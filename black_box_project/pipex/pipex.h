/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 01:01:57 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 17:49:32 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**envp;

	int		infile_fd;
	int		outfile_fd;

	int		fd_pip[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		exit_status;
}			t_pipex;

void		init_pipex(t_pipex *px, char **argv, char **envp);
void		open_files(t_pipex *px);
void		close_files(t_pipex *px);
char		*get_path_from_envp(char **envp);
char		*find_cmd_path(char *cmd, char **envp);
char		*build_cmd_path(char *dir, char *cmd);
char		*search_in_paths(char *cmd, char *path);
void		setup_first_child(t_pipex *px);
void		setup_second_child(t_pipex *px);
pid_t		safe_fork(t_pipex *px);
void		execute_cmd(t_pipex *px, char *cmd);
void		free_cmds(char **cmds);
void		error_exit(t_pipex *px, char *msg);
void		child_error_exit(t_pipex *px, char *msg);
void		create_pipe_and_fork_children(t_pipex *px);
void		close_and_wait_children(t_pipex *px);

#endif
