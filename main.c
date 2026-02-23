


#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void print_redirections(t_redirection *r)
{
    while (r)
    {
        printf("    REDIR type=%d file=%s\n", r->type, r->filename);
        r = r->next;
    }
}

void print_ast(t_ast *ast, int depth)
{
    if (!ast)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    if (ast->type == NODE_COMMAND)
    {
        printf("COMMAND\n");

        for (int i = 0; ast->cmd->args && ast->cmd->args[i]; i++)
        {
            for (int j = 0; j < depth + 1; j++)
                printf("  ");
            printf("ARG: %s\n", ast->cmd->args[i]);
        }

        if (ast->cmd->redirections)
        {
            for (int j = 0; j < depth + 1; j++)
                printf("  ");
            printf("REDIRECTIONS:\n");
            print_redirections(ast->cmd->redirections);
        }
    }
    else if (ast->type == NODE_PIPE)
    {
        printf("PIPE\n");
        print_ast(ast->pipe.left, depth + 1);
        print_ast(ast->pipe.right, depth + 1);
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_token *tokens;
    t_ast   *ast;

    (void)argc;
    (void)argv;

    while (1)
    {
        input = readline("minishell-test$ ");
        if (!input)
            break;

        if (*input)
            add_history(input);

        // 🔹 1) lexer
        tokens = lexer(input);   // عدّل الاسم حسب مشروعك

        if (!tokens)
        {
            printf("Lexer error\n");
            free(input);
            continue;
        }

        // 🔹 2) syntax check
        if (!syntax_check(tokens))
        {
            printf("Syntax error\n");
            free_tokens(tokens); // تأكد عندك free_tokens
            free(input);
            continue;
        }

        // 🔹 3) parse
        ast = parse_pipeline(&tokens);
        if (!ast)
        {
            printf("Parse error\n");
            free_tokens(tokens);
            free(input);
            continue;
        }

        // 🔹 4) print AST
        printf("=== AST ===\n");
        print_ast(ast, 0);

        // 🔹 5) cleanup
        free_ast(ast);
        free_tokens(tokens);
        free(input);
    }

    return (0);
}


// #include "minishell.h"

// static t_env *create_node(char *env_line)
// {
//     t_env  *node;
//     char   *equal;
//     int     key_len;

//     node = malloc(sizeof(t_env));
//     if (!node)
//         return (NULL);

//     equal = ft_strchr(env_line, '=');
//     if (!equal)
//     {
//         free(node);
//         return (NULL);
//     }

//     key_len = equal - env_line;
//     node->key = ft_substr(env_line, 0, key_len);
//     node->value = ft_strdup(equal + 1);
//     node->next = NULL;

//     if (!node->key || !node->value)
//         return (free(node->key), free(node->value), free(node), NULL);

//     return (node);
// }

// t_env *init_env(char **envp)
// {
//     t_env  *head;
//     t_env  *current;
//     t_env  *new_node;
//     int     i;

//     head = NULL;
//     current = NULL;
//     i = 0;

//     while (envp[i])
//     {
//         new_node = create_node(envp[i]);
//         if (!new_node)
//             return (NULL);

//         if (!head)
//             head = new_node;
//         else
//             current->next = new_node;

//         current = new_node;
//         i++;
//     }
//     return (head);
// }

// void free_env(t_env *env)
// {
//     t_env *tmp;

//     while (env)
//     {
//         tmp = env;
//         env = env->next;
//         free(tmp->key);
//         free(tmp->value);
//         free(tmp);
//     }
// }

// int main(int argc, char **argv, char **envp)
// {
//     t_env   *env;
//     char    *result;
//     char    *input;
//     int     last_status;

//     (void)argc;
//     (void)argv;

//     last_status = 0;
//     env = init_env(envp);

//     while (1)
//     {
//         input = readline("test> ");
//         if (!input)
//             break;

//         result = expand_string(input, env, last_status);
//         if (result)
//         {
//             printf("RESULT: [%s]\n", result);
//             free(result);
//         }

//         free(input);
//     }

//     free_env(env);
//     return (0);
// }


// // test case  : 
// // $USER
// // hello$USER
// // "$USER"
// // '$USER'
// // "$USER$HOME"
// // $UNDEFINED
// // $
// // $$
// // $?

// // valgrind ./minishell




// //extern char **environ;

// // int	main(void)
// // {
// // 	char *input = NULL;
// // 	t_token *tokens;
// // 	t_cmd *cmds;

// // 	while (1)
// // 	{
// // 		if (isatty(0))
// // 		{
// // 			input = readline("minishell$ ");
// // 			if (input == NULL)
// // 			{
// // 				printf("exit\n");
// // 				break;
// // 			}
// // 			if (input[0])
// // 				add_history(input);
// // 		}
// // 		else
// // 		{
// // 			char buf[4096];
// // 			int bytes = read(0, buf, sizeof(buf) - 1);
// // 			if (bytes <= 0)
// // 				break;
// // 			buf[bytes] = '\0';
// // 			if (bytes > 0 && buf[bytes - 1] == '\n')
// // 				buf[bytes - 1] = '\0';
// // 			input = ft_strdup(buf);
// // 		}

// // 		if (!input)
// // 			continue;

// // 		if (input[0])
// // 		{
// // 			tokens = lexer(input);
// // 			if (!tokens)
// // 			{
// // 				free(input);
// // 				continue;
// // 			}
// // 			cmds = parser(tokens);
// // 			if (cmds)
// // 			{
// // 				if (cmds->cmd && ft_strncmp(cmds->cmd, "exit", 5) == 0)
// // 				{
// // 					builtin_exit(cmds, input, tokens);
// // 					break;
// // 				}
// // 				executor(cmds, environ);
// // 			}
// // 			free_tokens(tokens);
// // 			free_command_list(cmds);
// // 		}
// // 		free(input);
// // 		input = NULL;
// // 	}
// // 	return (0);
// // }

// #include "minishell.h"


// int main(int argc, char **argv, char **envp)// expand_string مش عارف كيف اربطها
// {
//     t_token *tokens;
//     t_cmd   *cmds;
//     t_ast   *ast;
//     char    *input;

//     (void)argc;
//     (void)argv;

//     while (1)
//     {
//         input = readline("minishell$ ");
//         if (!input)
//         {
//             printf("exit\n");
//             break;
//         }
//         if (*input)
//             add_history(input);
//         tokens = lexer(input);
//         if (!tokens)
//         {
//             free(input);
//             continue;
//         }
//         if (!syntax_check(tokens))
//         {
//             printf("syntax error\n");
//             free_tokens(tokens);
//             free(input);
//             continue;
//         }
//         cmds = parser(tokens);
//         if (!cmds)
//         {
//             free_tokens(tokens);
//             free(input);
//             continue;
//         }
//         ast = build_ast_from_cmds(cmds);
//         if (!ast)
//         {
//             free_command_list(cmds);
//             free_tokens(tokens);
//             free(input);
//             continue;
//         }
//         execute_ast(ast, envp);
//         free_ast(ast);
//         free_command_list(cmds);
//         free_tokens(tokens);
//         free(input);
//     }
//     return (0);
// }
// // دخل قيمه احفضها بلهستوري اعملها توكن و شيك لها سينتكس  و اذا ما فيها مشاكل اعمل لها بارسنج و بعدين ابني منها شجره و في الاخر انفذها و حرر كل الذاكره اللي استخدمتها في كل مرحله