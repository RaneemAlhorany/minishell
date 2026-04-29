/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:58 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:41:18 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_last_arg_from_ast(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->type == NODE_COMMAND)
		return (get_last_arg_from_cmd(ast->cmd));
	if (ast->type == NODE_PIPE || ast->type == NODE_AND || ast->type == NODE_OR)
		return (get_last_arg_from_ast(ast->s_pipe.right));
	if (ast->type == NODE_GROUP)
		return (get_last_arg_from_ast(ast->s_pipe.left));
	return (NULL);
}

char	*get_last_arg_from_cmd(t_cmd *cmd)
{
	int		i;
	char	*last;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	i = 0;
	last = cmd->args[0];
	while (cmd->args[i])
	{
		last = cmd->args[i];
		i++;
	}
	return (last);
}
