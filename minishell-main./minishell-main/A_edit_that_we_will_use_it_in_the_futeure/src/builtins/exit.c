#include "minishell.h"

int	builtin_exit(t_cmd *cmd, char *input, t_token *tokens)
{
	free_tokens(tokens);
	free_command_list(cmd);
	free(input);
	return (0);
}
