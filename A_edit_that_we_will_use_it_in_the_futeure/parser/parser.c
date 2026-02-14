#include "minishell.h"

int	count_words_in_cmd(t_token *start)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = start;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			count++;
		else if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT
			|| tmp->type == TOKEN_REDIRECT_APPEND || tmp->type == TOKEN_HEREDOC)
		{
			if (tmp->next)// i know iam smart hahaha
				tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

void	init_cmd_node(t_cmd *node)
{
	node->cmd = NULL;
	node->args = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->infile_fd = -1;
	node->outfile_fd = -1;
	node->is_builtin = 0;
	node->append = 0;
	node->is_heredoc = 0;
	node->next = NULL;
}

void	handle_heredoc(t_token **tmp, t_cmd *node)
{
	if ((*tmp)->next)
		node->infile = ft_strdup((*tmp)->next->value);
	node->is_heredoc = 1;
	if ((*tmp)->next)
		*tmp = (*tmp)->next;
}

void	process_redirect_token(t_token **tmp, t_cmd *node)
{
	if ((*tmp)->type == TOKEN_REDIRECT_IN)
    {
	    if ((*tmp)->next)
	    	node->infile = ft_strdup((*tmp)->next->value);
    	if ((*tmp)->next)
    		*tmp = (*tmp)->next;
    }
	else if ((*tmp)->type == TOKEN_REDIRECT_OUT)
    {
        if ((*tmp)->next)
        	node->outfile = ft_strdup((*tmp)->next->value);
        node->append = 0;
    	if ((*tmp)->next)
    		*tmp = (*tmp)->next;
    }
    else if ((*tmp)->type == TOKEN_REDIRECT_APPEND)
    {
        if ((*tmp)->next)
        	node->outfile = ft_strdup((*tmp)->next->value);
        node->append = 1;
    	if ((*tmp)->next)
            *tmp = (*tmp)->next;
    }
	else if ((*tmp)->type == TOKEN_HEREDOC)
		handle_heredoc(tmp, node);
}

void	fill_args_loop(t_token *tk, t_cmd *node, int word_count)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = tk;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			node->args[i++] = ft_strdup(tmp->value);
		else if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT
			|| tmp->type == TOKEN_REDIRECT_APPEND || tmp->type == TOKEN_HEREDOC)
			process_redirect_token(&tmp, node);
		if (tmp)
			tmp = tmp->next;
	}
	node->args[word_count] = NULL;
}


t_cmd	*parse_single_cmd(t_token *tk)
{
	t_cmd	*node;
	int		word_count;

	word_count = count_words_in_cmd(tk);
	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	init_cmd_node(node);
	if (word_count > 0)
    {
        node->args = malloc(sizeof(char *) * (word_count + 1));
        if (!node->args)
        {
            free(node);
            return (NULL);
        }
        fill_args_loop(tk, node, word_count);
        if (node->args[0])
            node->cmd = ft_strdup(node->args[0]);
    }
	return (node);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	t_cmd	*node;
	t_token	*tk;

	head = NULL;
	current = NULL;
	tk = tokens;
	while (tk)
	{
		node = parse_single_cmd(tk);
		if (!node)
			return (NULL);
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
        while (tk && tk->type != TOKEN_PIPE)
		tk = tk->next;
	    if (tk && tk->type == TOKEN_PIPE)
		tk = tk->next;
    }
	return (head);
}

void	free_cmd_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_command_list(t_cmd *cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmds)
		return ;
	current = cmds;
	while (current)
	{
		next = current->next;
        if (current->cmd)
            free(current->cmd);
        if (current->args)
            free_cmd_args(current->args);
        if (current->infile)
            free(current->infile);
        if (current->outfile)
            free(current->outfile);
		free(current);
		current = next;
	}
}
