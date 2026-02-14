
#include "minishell.h"
#include <unistd.h>

extern char **environ;

int	main(void)
{
	char *input = NULL;
	t_token *tokens;
	t_cmd *cmds;

	while (1)
	{
		if (isatty(0))
		{
			input = readline("minishell$ ");
			if (input == NULL)
			{
				printf("exit\n");
				break;
			}
			if (input[0])
				add_history(input);
		}
		else
		{
			char buf[4096];
			int bytes = read(0, buf, sizeof(buf) - 1);
			if (bytes <= 0)
				break;
			buf[bytes] = '\0';
			if (bytes > 0 && buf[bytes - 1] == '\n')
				buf[bytes - 1] = '\0';
			input = ft_strdup(buf);
		}

		if (!input)
			continue;

		if (input[0])
		{
			tokens = lexer(input);
			if (!tokens)
			{
				free(input);
				continue;
			}
			cmds = parser(tokens);
			if (cmds)
			{
				if (cmds->cmd && ft_strncmp(cmds->cmd, "exit", 5) == 0)
				{
					builtin_exit(cmds, input, tokens);
					break;
				}
				executor(cmds, environ);
			}
			free_tokens(tokens);
			free_command_list(cmds);
		}
		free(input);
		input = NULL;
	}
	return (0);
}
