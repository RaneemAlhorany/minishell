
#include "minishell.h"
#include <stdio.h>

// دالة مساعدة لإنشاء عقدة أمر يدوياً للاختبار
t_ast *current_test_cmd(char **args, t_redirection *redirs)
{
    t_ast *node = malloc(sizeof(t_ast));
    node->type = NODE_COMMAND;
    node->cmd = malloc(sizeof(t_cmd));
    node->cmd->args = args;
    node->cmd->redirections = redirs;
    return (node);
}

int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    t_ast   *test_node;
    int     status;

    (void)argc;
    (void)argv;

    // 1. تهيئة الشيل والبيئة
    shell = init_shell(envp);
    shell->is_running = 1;

    printf("--- Start Minishell Executor Test ---\n");

    /* اختبار 1: تنفيذ أمر خارجي مع إعادة توجيه
       الأمر المحاكى: ls -l > test_output.txt
    */
    char *args1[] = {"ls", "-l", NULL};
    t_redirection redir1 = {"test_output.txt", NULL, TOKEN_REDIRECT_OUT};
    
    test_node = current_test_cmd(args1, &redir1);
    
    printf("Executing: ls -l > test_output.txt\n");
    status = execute_ast(test_node, shell);
    printf("Exit Status: %d\n", status);
    
    free(test_node->cmd);
    free(test_node);

    printf("-------------------------------------\n");

    /* اختبار 2: تنفيذ أمر Built-in (pwd)
    */
    char *args2[] = {"pwd", NULL};
    test_node = current_test_cmd(args2, NULL);
    
    printf("Executing: pwd\n");
    status = execute_ast(test_node, shell);
    printf("Exit Status: %d\n", status);

    free(test_node->cmd);
    free(test_node);

    printf("--- Test Finished ---\n");

    return (0);
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


