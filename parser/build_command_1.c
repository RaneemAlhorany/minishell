
#include "parsing.h"

static int	count_unquoted_words(const char *s)
{
    int	count;

    count = 0;
    if (!s)
        return (0);
    while (*s)
    {
        while (*s == ' ' || *s == '\t' || *s == '\n')
            s++;
        if (!*s)
            break ;
        count++;
        while (*s && *s != ' ' && *s != '\t' && *s != '\n')
            s++;
    }
    return (count);
}


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
    while (tmp && !is_command_delimiter(tmp->type))
	{
		if (tmp->type == TOKEN_WORD)
        {
            if (tmp->quoted)
                count++;
            else
                count += count_unquoted_words(tmp->value);
        }
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
    int   i;

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
    i = 0;
    while (i <= argc)
    {
        cmd->args[i] = NULL;
        i++;
    }
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




