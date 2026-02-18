/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_errors_bonus_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:05:32 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/22 18:05:33 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmds(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	close_pipes(t_pipex *px)
{
	int	i;

	if (!px || !px->pipes)
		return ;
	i = 0;
	while (i < px->cmd_count - 1)
	{
		if (px->pipes[i])
		{
			if (px->pipes[i][0] != -1)
				close(px->pipes[i][0]);
			if (px->pipes[i][1] != -1)
				close(px->pipes[i][1]);
		}
		i++;
	}
}

void	free_all_paths(t_pipex *px)
{
	if (!px || !px->paths)
		return ;
	free_cmds(px->paths);
	px->paths = NULL;
}

void	free_pipes_memory(t_pipex *px)
{
	int	i;

	if (!px || !px->pipes)
		return ;
	i = 0;
	while (i < px->cmd_count - 1)
	{
		free(px->pipes[i]);
		i++;
	}
	free(px->pipes);
	px->pipes = NULL;
}
