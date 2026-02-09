/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_errors_bonus_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:50:45 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 20:21:24 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	cleanup_pipex(t_pipex *px)
{
	if (!px)
		return ;
	close_files(px);
	close_pipes(px);
	free_cmds(px->cmds);
	px->cmds = NULL;
	free_all_paths(px);
	free_pipes_memory(px);
	if (px->pids)
	{
		free(px->pids);
		px->pids = NULL;
	}
}

void	child_error_exit(t_pipex *px, char *msg)
{
	if (msg)
		perror(msg);
	if (px)
		cleanup_pipex(px);
	exit(EXIT_FAILURE);
}

void	error_exit(t_pipex *px, char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("pipex fail");
	cleanup_pipex(px);
	exit(EXIT_FAILURE);
}

void	child_cmd_not_found(t_pipex *px, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(cmd);
	if (px)
		cleanup_pipex(px);
	exit(127);
}
