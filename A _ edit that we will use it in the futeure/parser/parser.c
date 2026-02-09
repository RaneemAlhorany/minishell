#include "minishell.h"

t_cmd	*parser(t_token *tokens) //Convert tokens into executable commands ///////We will do it later.
{
	(void)tokens;
	return (NULL);
}

void	free_cmds(t_cmd *cmds) //The same as in pipex project but for t_cmd struct
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!cmds)
		return ;
	current = cmds;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		free(current);
		current = next;
	}
}
