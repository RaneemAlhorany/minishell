
#include "parsing.h"





t_ast	*create_binary_node(t_node_type type, t_ast *left, t_ast *right)
{
    t_ast	*node;

    node = create_ast_node(type);
    if (!node)
    {
        free_ast(left);
        free_ast(right);
        return (NULL);
    }
    node->pipe.left = left;
    node->pipe.right = right;
    return (node);
}

t_ast	*create_ast_node(t_node_type type)
{
    t_ast	*node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    if (type == NODE_COMMAND)
        node->cmd = NULL;
    else if (type == NODE_PIPE || type == NODE_AND || type == NODE_OR
        || type == NODE_GROUP)
    {
        node->pipe.left = NULL;
        node->pipe.right = NULL;
    }
    return (node);
}

 t_ast	*parse_group_expression(t_token **tokens)
{
	t_ast	*node;
	t_ast	*group;

	*tokens = (*tokens)->next; // skip '('
	if (!*tokens)
		return (NULL);
	node = parse_and_expression(tokens);
	if (!node)
		return (NULL);
	if (!*tokens || (*tokens)->type != TOKEN_RPAREN)
	{
		free_ast(node);
		return (NULL);
	}
	*tokens = (*tokens)->next; // skip ')'
	group = create_ast_node(NODE_GROUP);
	if (!group)
	{
		free_ast(node);
		return (NULL);
	}
	group->pipe.left = node;
	return (group);
}


 int	is_primary_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_WORD)
		return (1);
	if (is_redirection(token->type))
		return (1);
	return (0);
}

t_ast	*parse_primary_expression(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_LPAREN)
		return (parse_group_expression(tokens));
	if (!is_primary_token(*tokens))
		return (NULL);
	return (build_command(tokens));
}

