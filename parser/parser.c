/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:06 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:40:51 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		node->s_pipe.left = NULL;
		node->s_pipe.right = NULL;
	}
	return (node);
}

t_ast	*parse_group_expression(t_token **tokens)
{
	t_ast	*node;
	t_ast	*group;

	*tokens = (*tokens)->next;
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
	*tokens = (*tokens)->next;
	group = create_ast_node(NODE_GROUP);
	if (!group)
	{
		free_ast(node);
		return (NULL);
	}
	group->s_pipe.left = node;
	return (group);
}

t_ast	*parse_pipe_expression(t_token **tokens)
{
	t_ast	*left;
	t_ast	*pre;

	left = NULL;
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_LPAREN)
		left = parse_group_expression(tokens);
	else if ((*tokens)->type == TOKEN_WORD || is_redirection((*tokens)->type))
		left = build_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		pre = left;
		left = parse_pipe_right(tokens, left);
		if (!left)
		{
			if (pre)
				free_ast(pre);
			return (NULL);
		}
	}
	return (left);
}

t_ast	*parse_and_expression(t_token **tokens)
{
	t_ast	*left;
	t_ast	*pre;

	left = parse_pipe_expression(tokens);
	if (!left)
		return (NULL);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		pre = left;
		left = parse_next_expression(tokens, left);
		if (!left)
		{
			if (pre)
				free_ast(pre);
			return (NULL);
		}
	}
	return (left);
}
