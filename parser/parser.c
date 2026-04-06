#include "parsing.h"


t_ast	*parse_pipe_right(t_token **tokens, t_ast *left)
{
	t_ast	*right;
	t_ast	*node;

	*tokens = (*tokens)->next;
	if (!*tokens)
	{
		free_ast(left);
		return (NULL);
	}
	right = parse_primary_expression(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	node = create_binary_node(NODE_PIPE, left, right);
	if (!node)
		return (NULL);
	return (node);
}

t_ast	*parse_pipe_expression(t_token **tokens)
{
	t_ast	*left;

	left = parse_primary_expression(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		left = parse_pipe_right(tokens, left);
		if (!left)
			return (NULL);
	}
	return (left);
}


// t_ast	*parse_pipe_expression(t_token **tokens)
// {
//     t_ast	*left;
//     t_ast	*right;
//     t_ast	*node;

//     left = parse_primary_expression(tokens);
//     if (!left)
//         return (NULL);
//     while (*tokens && (*tokens)->type == TOKEN_PIPE)
//     {
//         *tokens = (*tokens)->next;
//         if (!*tokens)
//         {
//             free_ast(left);
//             return (NULL);
//         }
//         right = parse_primary_expression(tokens);
//         if (!right)
//         {
//             free_ast(left);
//             return (NULL);
//         }
//         node = create_binary_node(NODE_PIPE, left, right);
//         if (!node)
//             return (NULL);
//         left = node;
//     }
//     return (left);
// }





 t_ast	*parse_next_expression(t_token **tokens, t_ast *left)
{
	t_ast		*right;
	t_ast		*node;
	t_node_type	operator;

	if ((*tokens)->type == TOKEN_AND)
		operator = NODE_AND;
	else
		operator = NODE_OR;
	*tokens = (*tokens)->next;
	if (!*tokens)
	{
		free_ast(left);
		return (NULL);
	}
	right = parse_pipe_expression(tokens);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	node = create_binary_node(operator, left, right);
	if (!node)
		return (NULL);
	return (node);
}



t_ast	*parse_and_expression(t_token **tokens)
{
	t_ast	*left;

	left = parse_pipe_expression(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		left = parse_next_expression(tokens, left);
		if (!left)
			return (NULL);
	}
	return (left);
}







t_ast	*parse_pipeline(t_token **tokens)
{
    t_ast	*root;

    if (!tokens || !*tokens)
        return (NULL);
    root = parse_and_expression(tokens);
    if (!root)
        return (NULL);
    if (*tokens)
    {
        free_ast(root);
        return (NULL);
    }
    return (root);
}








// t_ast	*parse_and_expression(t_token **tokens)
// {
//     t_ast		*left;
//     t_ast		*right;
//     t_ast		*node;
//     t_node_type	operator;

//     left = parse_pipe_expression(tokens);
//     if (!left)
//         return (NULL);
//     while (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
//     {
//         if((*tokens)->type == TOKEN_AND)
//             operator = NODE_AND;
//         else
//             operator = NODE_OR;
//         *tokens = (*tokens)->next;
//         if (!*tokens)
//         {
//             free_ast(left);
//             return (NULL);
//         }
//         right = parse_pipe_expression(tokens);
//         if (!right)
//         {
//             free_ast(left);
//             return (NULL);
//         }
//         node = create_binary_node(operator, left, right);
//         if (!node)
//             return (NULL);
//         left = node;
//     }
//     return (left);
// }



// t_ast	*parse_primary_expression(t_token **tokens)
// {
//     t_ast	*node;
//     t_ast	*group;

//     if (!tokens || !*tokens)
//         return (NULL);
//     if ((*tokens)->type == TOKEN_LPAREN)
//     {
//         *tokens = (*tokens)->next;
//         if (!*tokens)
//             return (NULL);
//         node = parse_and_expression(tokens);
//         if (!node)
//             return (NULL);
//         if (!*tokens || (*tokens)->type != TOKEN_RPAREN)
//         {
//             free_ast(node);
//             return (NULL);
//         }
//         *tokens = (*tokens)->next;
//         group = create_ast_node(NODE_GROUP);
//         if (!group)
//         {
//             free_ast(node);
//             return (NULL);
//         }
//         group->pipe.left = node;
//         return (group);
//     }
//     if ((*tokens)->type != TOKEN_WORD && !is_redirection((*tokens)->type))
//         return (NULL);
//     return (build_command(tokens));
// }


