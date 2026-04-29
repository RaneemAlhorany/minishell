/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:19 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:39:46 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
	int	status;

	setup_execution_signal(0);
	if (shell)
		shell->in_child_process = 1;
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	status = execute_ast(node->s_pipe.right, shell);
	if (!(shell->active_ast))
		free_ast(node);
	free_parts(shell);
	free_shell(shell);
	rl_clear_history();
	exit(status);
}

pid_t	fork_right_process(t_ast *node, t_shell *shell, int pipe_fd[2],
		pid_t left_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(left_pid, NULL, 0);
		return (-1);
	}
	if (pid == 0)
		execute_right_child(node, shell, pipe_fd);
	return (pid);
}

void	execute_left_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
	int	status;

	setup_execution_signal(0);
	if (shell)
		shell->in_child_process = 1;
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	status = execute_ast(node->s_pipe.left, shell);
	if (!(shell->active_ast))
		free_ast(node);
	free_parts(shell);
	free_shell(shell);
	rl_clear_history();
	exit(status);
}

pid_t	fork_left_process(t_ast *node, t_shell *shell, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
		execute_left_child(node, shell, pipe_fd);
	return (pid);
}

int	execute_pipe_node(t_ast *node, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node || node->type != NODE_PIPE || !node->s_pipe.left
		|| !node->s_pipe.right)
		return (execute_command_node(node, shell));
	if (pipe(pipe_fd) == -1)
		return (1);
	left_pid = fork_left_process(node, shell, pipe_fd);
	if (left_pid < 0)
		return (1);
	right_pid = fork_right_process(node, shell, pipe_fd, left_pid);
	if (right_pid < 0)
		return (1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (wait_for_pipe(left_pid, right_pid));
}
