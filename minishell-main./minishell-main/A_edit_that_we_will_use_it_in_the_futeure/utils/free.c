#include "minishell.h"

void	cleanup(t_token *tokens, t_cmd *cmds) // don't used it yet, but I saw it in a summary
{
	free_tokens(tokens);
	free_command_list(cmds);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}