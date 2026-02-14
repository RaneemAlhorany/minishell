/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_here_doc_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:05:42 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/22 18:05:43 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(t_pipex *px)
{
	char	*line;

	if (pipe(px->here_pipe) == -1)
		error_exit(px, "pipe here_doc");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, px->limiter, ft_strlen(px->limiter))
			&& line[ft_strlen(px->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(px->here_pipe[1], line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
	close(px->here_pipe[1]);
	px->infile_fd = px->here_pipe[0];
}
