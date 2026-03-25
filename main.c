
#include "minishell.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signals/signals.h"

typedef struct s_test_case
{
    const char	*name;
    const char	*line;
    const char	*stdin_data;
    int			expect_status;
    int			run_in_child;
}   t_test_case;

static int	is_blank_line(const char *s)
{
    if (!s)
        return (1);
    while (*s)
    {
        if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r')
            return (0);
        s++;
    }
    return (1);
}

static int	expand_tokens(t_token *tokens, t_shell *shell)
{
    char	*expanded;

    while (tokens)
    {
        if (tokens->type == TOKEN_WORD)
        {
            expanded = expand_string(tokens->value, shell->env, shell->last_exit_status);
            if (!expanded)
                return (0);
            free(tokens->value);
            tokens->value = expanded;
        }
        tokens = tokens->next;
    }
    return (1);
}

static int	execute_line(t_shell *shell, const char *line)
{
    char	*input;
    t_token	*tokens;
    t_token	*tokens_head;
    t_ast	*ast;
    int		status;

    if (!shell || !line || is_blank_line(line))
        return (0);
    input = ft_strdup(line);
    if (!input)
        return (1);
    tokens = lexer(input);
    free(input);
    if (!tokens)
        return (2);
    tokens_head = tokens;
    if (!expand_tokens(tokens, shell))
    {
        free_tokens(tokens_head);
        return (1);
    }
    if (!syntax_check(tokens))
    {
        free_tokens(tokens_head);
        return (2);
    }
    ast = parse_pipeline(&tokens);
    if (!ast)
    {
        free_tokens(tokens_head);
        return (2);
    }
    status = execute_ast(ast, shell);
    shell->last_exit_status = status;
    free_ast(ast);
    free_tokens(tokens_head);
    return (status);
}

static int	execute_line_in_child(char **envp, const char *line, const char *stdin_data)
{
    pid_t	pid;
    int		wstatus;
    int		pipe_fd[2];
    t_shell	*shell;

    pid = fork();
    if (pid < 0)
        return (1);
    if (pid == 0)
    {
        if (stdin_data)
        {
            if (pipe(pipe_fd) == 0)
            {
                (void)!write(pipe_fd[1], stdin_data, ft_strlen(stdin_data));
                close(pipe_fd[1]);
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[0]);
            }
        }
        shell = init_shell(envp);
        if (!shell)
            exit(1);
        exit(execute_line(shell, line));
    }
    if (waitpid(pid, &wstatus, 0) < 0)
        return (1);
    if (WIFEXITED(wstatus))
        return (WEXITSTATUS(wstatus));
    if (WIFSIGNALED(wstatus))
        return (128 + WTERMSIG(wstatus));
    return (1);
}

static void	print_usage(const char *prog)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s                 # interactive\n", prog);
    fprintf(stderr, "  %s --test           # run built-in test suite\n", prog);
    fprintf(stderr, "  %s --cmd  <line>    # run one command line\n", prog);
    fprintf(stderr, "  %s --file <path>    # run script file (one command per line)\n", prog);
}

static char	*trim_newline(char *s)
{
    size_t	len;

    if (!s)
        return (NULL);
    len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
    {
        s[len - 1] = '\0';
        len--;
    }
    return (s);
}

static int	run_script_file(t_shell *shell, const char *path)
{
    FILE	*fp;
    char	buf[4096];
    int		status;

    status = 0;
    fp = fopen(path, "r");
    if (!fp)
    {
        fprintf(stderr, "minishell: cannot open %s: %s\n", path, strerror(errno));
        return (1);
    }
    while (fgets(buf, (int)sizeof(buf), fp))
    {
        trim_newline(buf);
        if (buf[0] == '#' || is_blank_line(buf))
            continue;
        status = execute_line(shell, buf);
    }
    fclose(fp);
    return (status);
}

static int	run_test_suite(t_shell *shell, char **envp)
{
    const t_test_case	tests[] = {
        {"echo builtin", "echo hello", NULL, 0, 0},
        {"double quotes + expansion", "echo \"$USER\"", NULL, 0, 0},
        {"single quotes no expansion", "echo '$USER'", NULL, 0, 0},
        {"export var", "export TEST_MINISHELL=42", NULL, 0, 0},
        {"expand var", "echo $TEST_MINISHELL", NULL, 0, 0},
        {"unset var", "unset TEST_MINISHELL", NULL, 0, 0},
        {"pipe", "echo hello | wc -c", NULL, 0, 0},
        {"redir out", "echo first > test_output.txt", NULL, 0, 0},
        {"redir append", "echo second >> test_output.txt", NULL, 0, 0},
        {"redir in + pipe", "cat < test_output.txt | wc -l", NULL, 0, 0},
        {"syntax error", "| ls", NULL, 2, 0},
        {"heredoc", "cat << EOF | wc -c", "abc\nEOF\n", 0, 1},
        {"exit builtin (child)", "exit 7", NULL, 7, 1},
    };
    int				pass;
    int				fail;
    int				status;
    size_t			i;

    pass = 0;
    fail = 0;
    i = 0;
    printf("--- minishell: test suite ---\n");
    while (i < (sizeof(tests) / sizeof(tests[0])))
    {
        if (tests[i].run_in_child)
            status = execute_line_in_child(envp, tests[i].line, tests[i].stdin_data);
        else
            status = execute_line(shell, tests[i].line);
        if (tests[i].expect_status != -1 && status != tests[i].expect_status)
        {
            printf("[FAIL] %s: `%s` -> got %d (expected %d)\n",
                tests[i].name, tests[i].line, status, tests[i].expect_status);
            fail++;
        }
        else
        {
            printf("[PASS] %s\n", tests[i].name);
            pass++;
        }
        i++;
    }
    printf("--- summary: %d pass, %d fail ---\n", pass, fail);
    return (fail == 0);
}

static int	interactive_loop(t_shell *shell)
{
    char	*input;

    setup_signals();
    while (shell->is_running)
    {
        set_interactive_readline_mode(1);
        input = readline("minishell$ ");
        set_interactive_readline_mode(0);
        if (!input)
        {
            if (g_last_signal == SIGINT)
            {
                clear_last_signal();
                continue;
            }
            printf("exit\n");
            break ;
        }
        if (get_last_signal() == SIGINT)
        {
            shell->last_exit_status = 130;
            clear_last_signal();
        }
        if (*input)
            add_history(input);
        if (!is_blank_line(input))
            shell->last_exit_status = execute_line(shell, input);
        free(input);
    }
    return (shell->last_exit_status);
}

int	main(int argc, char **argv, char **envp)
{
    t_shell	*shell;
    int		status;

    shell = init_shell(envp);
    if (!shell)
        return (1);
    status = 0;
    if (argc >= 2 && strcmp(argv[1], "--test") == 0)
    {
        status = (run_test_suite(shell, envp) ? 0 : 1);
    }
    else if (argc >= 3 && strcmp(argv[1], "--cmd") == 0)
    {
        status = execute_line(shell, argv[2]);
    }
    else if (argc >= 3 && strcmp(argv[1], "--file") == 0)
    {
        status = run_script_file(shell, argv[2]);
    }
    else if (argc == 1)
    {
        status = interactive_loop(shell);
    }
    else
    {
        print_usage(argv[0]);
        status = 2;
    }
    free_env_list(shell->env);
    free(shell);
    return (status);
}






// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include "minishell.h"



// static void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("TOKEN: type=%d value=%s\n", tokens->type, tokens->value);
// 		tokens = tokens->next;
// 	}
// }

// static int	expand_tokens(t_token *tokens, t_shell *shell)
// {
// 	char *expanded;
// 	while (tokens)
// 	{
// 		if (tokens->type == TOKEN_WORD)
// 		{
// 			expanded = expand_string(tokens->value, shell->env, shell->last_exit_status);
// 			if (!expanded)
// 				return (0);
// 			free(tokens->value);
// 			tokens->value = expanded;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (1);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*tokens;
// 	t_ast	*ast;
// 	t_shell	*shell;

// 	(void)argc;
// 	(void)argv;

// 	shell = init_shell(envp);
// 	if (!shell)
// 		return (1);

// 	while (shell->is_running)
// 	{
// 		input = readline("minishell$ ");

// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}

// 		if (*input)
// 			add_history(input);

// 		// LEXER
// 		tokens = lexer(input);
// 		if (!tokens)
// 		{
// 			free(input);
// 			continue ;
// 		}

// 		// DEBUG TOKENS
// 		print_tokens(tokens);

// 		// EXPANSION
// 		if (!expand_tokens(tokens, shell))
// 		{
// 			printf("Expansion error\n");
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}

// 		// SYNTAX CHECK
// 		if (!syntax_check(tokens))
// 		{
// 			printf("Syntax error\n");
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}

// 		// PARSER
// 		ast = parse_pipeline(&tokens);
// 		if (!ast)
// 		{
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}

// 		// EXECUTION
// 		shell->last_exit_status = execute_ast(ast, shell);

// 		free_ast(ast);
// 		free_tokens(tokens);
// 		free(input);
// 	}

// 	int exit_status = shell->last_exit_status;
// 	free_env_list(shell->env);
// 	free(shell);
// 	return (exit_status);
// }




// // int main(int argc, char **argv, char **envp)
// // {
// //     t_shell    shell;
// //     char       *input;

// //     (void)argc;
// //     (void)argv;

// //     shell = init_shell(envp);
// //     if (!shell.env)
// //         return (1);

// //     while (shell.is_running)
// //     {
// //         input = readline("minishell$ ");

// //         /* Ctrl + D */
// //         if (!input)
// //         {
// //             printf("exit\n");
// //             break;
// //         }

// //         /* Empty input */
// //         if (*input == '\0')
// //         {
// //             free(input);
// //             continue;
// //         }

// //         add_history(input);

// //         /* لاحقًا:
// //            - parsing
// //            - execution
// //         */

// //         free(input);
// //     }

// //     free_env_list(shell.env);
// //     return (shell.last_exit_status);
// // }




// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>
// #include "minishell.h"



// static void	print_tokens(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("TOKEN: type=%d value=%s\n", tokens->type, tokens->value);
// 		tokens = tokens->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*tokens;
// 	t_ast	*ast;
// 	t_shell	shell;

// 	(void)argc;
// 	(void)argv;

// 	shell.env = build_env_list(envp);
// 	shell.last_exit_status = 0;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");

// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}

// 		if (*input)
// 			add_history(input);

// 		// LEXER
// 		tokens = lexer(input);
// 		if (!tokens)
// 		{
// 			free(input);
// 			continue ;
// 		}

// 		// DEBUG TOKENS
// 		print_tokens(tokens);

// 		// SYNTAX CHECK
// 		if (!syntax_check(tokens))
// 		{
// 			printf("Syntax error\n");
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}

// 		// PARSER
// 		ast = parse_pipeline(&tokens);
// 		if (!ast)
// 		{
// 			free_tokens(tokens);
// 			free(input);
// 			continue ;
// 		}

// 		// EXECUTION
// 		execute_ast(ast, &shell);

// 		free_ast(ast);
// 		free_tokens(tokens);
// 		free(input);
// 	}

// 	free_env_list(shell.env);
// 	return (0);
// }




// int main(int argc, char **argv, char **envp)
// {
//     t_shell    shell;
//     char       *input;

//     (void)argc;
//     (void)argv;

//     shell = init_shell(envp);
//     if (!shell.env)
//         return (1);

//     while (shell.is_running)
//     {
//         input = readline("minishell$ ");

//         /* Ctrl + D */
//         if (!input)
//         {
//             printf("exit\n");
//             break;
//         }

//         /* Empty input */
//         if (*input == '\0')
//         {
//             free(input);
//             continue;
//         }

//         add_history(input);

//         /* لاحقًا:
//            - parsing
//            - execution
//         */

//         free(input);
//     }

//     free_env_list(shell.env);
//     return (shell.last_exit_status);
// }


