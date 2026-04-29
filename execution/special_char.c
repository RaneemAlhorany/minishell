/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:04 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:40:17 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_child(t_ast *node, t_shell *shell)
{
	int	status;

	setup_child_signals();
	if (shell)
		shell->in_child_process = 1;
	status = execute_ast(node->s_pipe.left, shell);
	if (!(shell->active_ast))
		free_ast(node);
	free_parts(shell);
	free_shell(shell);
	rl_clear_history();
	exit(status);
	return (status);
}

int	execute_group_node(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execute_child(node, shell);
	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if ((status & 0x7F) == 0)
		return ((status >> 8) & 0xFF);
	if ((status & 0x7F) != 0)
	{
		g_last_signal = status & 0x7F;
		return (128 + g_last_signal);
	}
	return (1);
}

int	execute_logical_node(t_ast *node, t_shell *shell)
{
	int	status;

	status = execute_ast(node->s_pipe.left, shell);
	if (shell)
		shell->last_exit_status = status;
	if (!shell || !shell->is_running)
		return (status);
	if (node->type == NODE_AND && status == 0)
	{
		status = execute_ast(node->s_pipe.right, shell);
		if (shell)
			shell->last_exit_status = status;
		return (status);
	}
	if (node->type == NODE_OR && status != 0)
	{
		status = execute_ast(node->s_pipe.right, shell);
		if (shell)
			shell->last_exit_status = status;
		return (status);
	}
	return (status);
}
