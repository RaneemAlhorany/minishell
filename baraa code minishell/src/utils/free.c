#include "minishell.h"

void	cleanup(t_token *tokens, t_cmd *cmds) // don't used it yet, but I saw it in a summary
{
	free_tokens(tokens);
	free_cmds(cmds);
}
