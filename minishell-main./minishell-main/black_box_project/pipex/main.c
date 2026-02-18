/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 00:57:22 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/21 16:51:42 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (1);
	}
	init_pipex(&px, argv, envp);
	open_files(&px);
	create_pipe_and_fork_children(&px);
	close_and_wait_children(&px);
	return (px.exit_status);
}
