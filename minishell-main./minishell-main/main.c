
#include "minishell.h"

static t_env *create_node(char *env_line)
{
    t_env  *node;
    char   *equal;
    int     key_len;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);

    equal = ft_strchr(env_line, '=');
    if (!equal)
    {
        free(node);
        return (NULL);
    }

    key_len = equal - env_line;
    node->key = ft_substr(env_line, 0, key_len);
    node->value = ft_strdup(equal + 1);
    node->next = NULL;

    if (!node->key || !node->value)
        return (free(node->key), free(node->value), free(node), NULL);

    return (node);
}

t_env *init_env(char **envp)
{
    t_env  *head;
    t_env  *current;
    t_env  *new_node;
    int     i;

    head = NULL;
    current = NULL;
    i = 0;

    while (envp[i])
    {
        new_node = create_node(envp[i]);
        if (!new_node)
            return (NULL);

        if (!head)
            head = new_node;
        else
            current->next = new_node;

        current = new_node;
        i++;
    }
    return (head);
}

void free_env(t_env *env)
{
    t_env *tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_env   *env;
    char    *result;
    char    *input;
    int     last_status;

    (void)argc;
    (void)argv;

    last_status = 0;
    env = init_env(envp);

    while (1)
    {
        input = readline("test> ");
        if (!input)
            break;

        result = expand_string(input, env, last_status);
        if (result)
        {
            printf("RESULT: [%s]\n", result);
            free(result);
        }

        free(input);
    }

    free_env(env);
    return (0);
}


// test case  : 
// $USER
// hello$USER
// "$USER"
// '$USER'
// "$USER$HOME"
// $UNDEFINED
// $
// $$
// $?

// valgrind ./minishell




//extern char **environ;

// int	main(void)
// {
// 	char *input = NULL;
// 	t_token *tokens;
// 	t_cmd *cmds;

// 	while (1)
// 	{
// 		if (isatty(0))
// 		{
// 			input = readline("minishell$ ");
// 			if (input == NULL)
// 			{
// 				printf("exit\n");
// 				break;
// 			}
// 			if (input[0])
// 				add_history(input);
// 		}
// 		else
// 		{
// 			char buf[4096];
// 			int bytes = read(0, buf, sizeof(buf) - 1);
// 			if (bytes <= 0)
// 				break;
// 			buf[bytes] = '\0';
// 			if (bytes > 0 && buf[bytes - 1] == '\n')
// 				buf[bytes - 1] = '\0';
// 			input = ft_strdup(buf);
// 		}

// 		if (!input)
// 			continue;

// 		if (input[0])
// 		{
// 			tokens = lexer(input);
// 			if (!tokens)
// 			{
// 				free(input);
// 				continue;
// 			}
// 			cmds = parser(tokens);
// 			if (cmds)
// 			{
// 				if (cmds->cmd && ft_strncmp(cmds->cmd, "exit", 5) == 0)
// 				{
// 					builtin_exit(cmds, input, tokens);
// 					break;
// 				}
// 				executor(cmds, environ);
// 			}
// 			free_tokens(tokens);
// 			free_command_list(cmds);
// 		}
// 		free(input);
// 		input = NULL;
// 	}
// 	return (0);
// }
