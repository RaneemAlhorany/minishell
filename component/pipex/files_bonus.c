/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:05:25 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/28 14:51:36 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_files(t_pipex *px)
{
	if (!px)
		return ;
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
	if (!px)
		return ;
	if (!px->is_here_doc)
	{
		px->infile_fd = open(px->infile, O_RDONLY);
		if (px->infile_fd == -1)
			perror(px->infile);
	}
	if (px->is_here_doc)
		px->outfile_fd = open(px->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		px->outfile_fd = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile_fd == -1)
		perror(px->outfile);
}

void	get_cmd_info(t_pipex *px, int argc, int *start)
{
	if (!px || argc < 5)
		error_exit(px, "invalid arguments");
	if (px->is_here_doc)
	{
		px->cmd_count = argc - 4;
		*start = 3;
	}
	else
	{
		px->cmd_count = argc - 3;
		*start = 2;
	}
	if (px->cmd_count <= 0)
		error_exit(px, "no commands provided");
}

void	parse_commands(t_pipex *px, int argc, char **argv)
{
	int	start;
	int	i;

	get_cmd_info(px, argc, &start);
	px->cmds = ft_calloc(px->cmd_count + 1, sizeof(char *));
	if (!px->cmds)
		error_exit(px, "malloc cmds array ERROR");
	i = 0;
	while (i < px->cmd_count)
	{
		if (!argv[start + i] || ft_strlen(argv[start + i]) == 0)
			child_error_exit(px, "Error: empty command");
		px->cmds[i] = ft_strdup(argv[start + i]);
		if (!px->cmds[i])
			error_exit(px, "malloc cmd string ERROR");
		i++;
	}
	px->cmds[i] = NULL;
}

void	wait_for_all_children(t_pipex *px)
{
	int		status;
	pid_t	pid;

	px->last_exit = 1;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == px->pids[px->cmd_count - 1])
		{
			if (WIFEXITED(status))
				px->last_exit = WEXITSTATUS(status);
			else
				px->last_exit = 1;
		}
		pid = waitpid(-1, &status, 0);
	}
}
