/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:33:27 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 20:21:30 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmds(char **cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	child_error_exit(t_pipex *px, char *msg)
{
	if (msg)
		perror(msg);
	if (px)
	{
		if (px->fd_pip[0] != -1)
			close(px->fd_pip[0]);
		if (px->fd_pip[1] != -1)
			close(px->fd_pip[1]);
		close_files(px);
	}
	exit(EXIT_FAILURE);
}

void	error_exit(t_pipex *px, char *msg)
{
	if (msg)
		perror(msg);
	else
		perror("wrong usage");
	close_files(px);
	exit(EXIT_FAILURE);
}
