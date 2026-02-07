/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 00:06:19 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 19:18:30 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_files(t_pipex *px)
{
	if (px->infile_fd != -1)
	{
		close(px->infile_fd);
		px->infile_fd = -1;
	}
	if (px->outfile_fd != -1)
	{
		close(px->outfile_fd);
		px->outfile_fd = -1;
	}
}

void	open_files(t_pipex *px)
{
	px->infile_fd = open(px->infile, O_RDONLY);
	if (px->infile_fd == -1)
		perror(px->infile);
	px->outfile_fd = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile_fd == -1)
		perror(px->outfile);
}

void	create_pipe_and_fork_children(t_pipex *px)
{
	if (pipe(px->fd_pip) == -1)
		error_exit(px, "pipe error");
	if (px->infile_fd != -1)
	{
		px->pid_1 = safe_fork(px);
		if (px->pid_1 == 0)
			setup_first_child(px);
	}
	else
		px->pid_1 = -1;
	if (px->outfile_fd != -1)
	{
		px->pid_2 = safe_fork(px);
		if (px->pid_2 == 0)
			setup_second_child(px);
	}
	else
		px->pid_2 = -1;
}
void	close_and_wait_children(t_pipex *px)
{
	int	status;

	close_files(px);
	close(px->fd_pip[0]);
	close(px->fd_pip[1]);



	if (px->pid_1 > 0)
		waitpid(px->pid_1, NULL, 0);

	if (px->pid_2 > 0)
	{
		waitpid(px->pid_2, &status, 0);
		if (WIFEXITED(status))
			px->exit_status = WEXITSTATUS(status);
		else
			px->exit_status = 1;
	}
	else
		px->exit_status = 1;
}


