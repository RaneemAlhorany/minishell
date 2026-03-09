
#include "parsing.h"



t_ast *build_command(t_token **tokens)
{
    t_ast *node;

    node = init_command_node(*tokens);
    if (!node)
        return (NULL);

    if (!fill_command_data(node, tokens))
    {
        free_command(node->cmd);
        free(node);
        return (NULL);
    }
    return (node);
}




 t_ast *init_command_node(t_token *tokens)
{
    t_ast  *node;
    int     argc;

    node = create_ast_node(NODE_COMMAND);
    if (!node)
        return (NULL);

    argc = count_words_in_cmd(tokens);
    node->cmd = create_cmd(argc);
    if (!node->cmd)
    {
        free(node);
        return (NULL);
    }
    return (node);
}





int	process_command_tokens(t_ast *node, t_token **tokens, int *has_word)
{
	int				index;
	t_redirection	*last_redir;

	index = 0;
	last_redir = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			if (!handle_word_token(node->cmd, *tokens, &index))
				return (0);
			*has_word = 1;
		}
		else if (is_redirection((*tokens)->type))
		{
			if (!handle_redirection_token(node->cmd, tokens, &last_redir))
				return (0);
		}
		else
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	fill_command_data(t_ast *node, t_token **tokens)
{
	int	has_word;

	has_word = 0;
	if (!process_command_tokens(node, tokens, &has_word))
		return (0);
	if (!has_word && !node->cmd->redirections)
		return (0);
	return (1);
}

 int handle_word_token(t_cmd *cmd, t_token *token, int *index)
{
    if (!token->value)
        return (0);
    cmd->args[*index] = strdup(token->value);
    if (!cmd->args[*index])
        return (0);
    (*index)++;
    return (1);
}

int handle_redirection_token(t_cmd *cmd,t_token **tokens, t_redirection **last)
{
    t_redirection *new_redir;

    if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
        return (0);
    new_redir = create_redirection(*tokens);
    if (!new_redir)
        return (0);

    add_redirection(cmd, new_redir, last);

    *tokens = (*tokens)->next; // skip filename
    return (1);
}
