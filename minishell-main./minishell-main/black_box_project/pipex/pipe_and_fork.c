/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:27:36 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 20:22:01 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(t_pipex *px, char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		child_error_exit(px, " error split");
	cmd_path = find_cmd_path(cmd_args[0], px->envp);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_cmds(cmd_args);
		close_files(px);
		exit(127);
	}
	execve(cmd_path, cmd_args, px->envp);
	perror(cmd_args[0]);
	free(cmd_path);
	free_cmds(cmd_args);
	close_files(px);
	exit(EXIT_FAILURE);
}

void	setup_first_child(t_pipex *px)
{
	if (dup2(px->infile_fd, STDIN_FILENO) == -1)
		child_error_exit(px, "dup2 infile ERROR");
	if (dup2(px->fd_pip[1], STDOUT_FILENO) == -1)
		child_error_exit(px, "dup2 pipe write ERROR");
	close(px->fd_pip[0]);
	close(px->fd_pip[1]);
	close_files(px);
	execute_cmd(px, px->cmd1);
}

void	setup_second_child(t_pipex *px)
{
	if (dup2(px->fd_pip[0], STDIN_FILENO) == -1)
		child_error_exit(px, "dup2 pipe read ERROR");
	if (dup2(px->outfile_fd, STDOUT_FILENO) == -1)
		child_error_exit(px, "dup2 outfile ERROR");
	close(px->fd_pip[0]);
	close(px->fd_pip[1]);
	close_files(px);
	execute_cmd(px, px->cmd2);
}

pid_t	safe_fork(t_pipex *px)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(px->fd_pip[0]);
		close(px->fd_pip[1]);
		error_exit(px, " ERROR fork");
	}
	return (pid);
}
