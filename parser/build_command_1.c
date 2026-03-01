
#include "parsing.h"


void	init_cmd(t_cmd *cmd)
{
    cmd->args = NULL;
    cmd->redirections = NULL;
}



int	count_words_in_cmd(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		else if (is_redirection(tmp->type))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

t_cmd *create_cmd(int argc)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    init_cmd(cmd);
    cmd->args = malloc(sizeof(char *) * (argc + 1));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    cmd->args[argc] = NULL;
    return (cmd);
}




t_redirection *create_redirection(t_token *current)
{
    t_redirection *new_redir;

    new_redir = malloc(sizeof(t_redirection));
    if (!new_redir)
        return (NULL);

    new_redir->type = current->type;
    if (!current->next)
    {
        free(new_redir);
        return (NULL);
    }
    new_redir->filename = strdup(current->next->value);
    if (!new_redir->filename)
    {
        free(new_redir);
        return (NULL);
    }
    new_redir->next = NULL;

    return (new_redir);
}


void add_redirection(t_cmd *cmd, t_redirection *new_redir, t_redirection **last)
{
    if (!cmd->redirections)
        cmd->redirections = new_redir;
    else
        (*last)->next = new_redir;

    *last = new_redir;
}





