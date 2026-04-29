/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:02 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:40:29 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parse_pipe_right(t_token **tokens, t_ast *left)
{
	t_ast	*right;
	t_ast	*node;

	*tokens = (*tokens)->next;
	if (!*tokens)
		return (NULL);
	right = parse_pipe_expression(tokens);
	if (!right)
		return (NULL);
	node = create_binary_node(NODE_PIPE, left, right);
	if (!node)
	{
		free_ast(right);
		return (NULL);
	}
	return (node);
}

t_ast	*create_binary_node(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = create_ast_node(type);
	if (!node)
		return (NULL);
	node->s_pipe.left = left;
	node->s_pipe.right = right;
	return (node);
}

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
		return (NULL);
	right = parse_pipe_expression(tokens);
	if (!right)
		return (NULL);
	node = create_binary_node(operator, left, right);
	if (!node)
	{
		free_ast(right);
		return (NULL);
	}
	return (node);
}
