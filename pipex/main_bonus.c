/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:54:46 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/22 17:39:55 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	ft_bzero(&px, sizeof(t_pipex));
	init_pipex(&px, argv, envp, argc);
	parse_commands(&px, argc, argv);
	if (px.is_here_doc)
		handle_here_doc(&px);
	open_files(&px);
	create_pipe_and_fork(&px);
	cleanup_pipex(&px);
	return (px.last_exit);
}
