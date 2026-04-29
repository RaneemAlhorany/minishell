/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:23 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:16:25 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_ast(t_ast *node, t_shell *shell)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (execute_command_node(node, shell));
	else if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, shell));
	else if (node->type == NODE_AND || node->type == NODE_OR)
		return (execute_logical_node(node, shell));
	else if (node->type == NODE_GROUP)
		return (execute_group_node(node, shell));
	return (0);
}
