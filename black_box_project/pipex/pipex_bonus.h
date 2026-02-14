/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:06:04 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/25 20:02:50 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./Libft/libft.h"
# include "./get_next_line/get_next_line.h"
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
	char	**envp;

	int		infile_fd;
	int		outfile_fd;

	char	**cmds;
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;
	char	**paths;
	int		is_here_doc;
	char	*limiter;
	int		here_pipe[2];
	int		last_exit;

}			t_pipex;

void		init_pipex(t_pipex *px, char **argv, char **envp, int argc);
void		open_files(t_pipex *px);
void		close_files(t_pipex *px);

void		parse_commands(t_pipex *px, int argc, char **argv);
void		execute_cmd(t_pipex *px, char *cmd);
void		setup_child_at_index(t_pipex *px, int i);

pid_t		safe_fork(t_pipex *px);
void		create_pipes(t_pipex *px);
void		create_pipe_and_fork(t_pipex *px);
void		close_pipes(t_pipex *px);

char		*get_path_from_env(char **envp);
char		*find_cmd_path(char *cmd, char **envp);
char		*build_cmd_path(char *dir, char *cmd);
char		*search_in_paths(char *cmd, char *path);

void		free_cmds(char **cmds);
void		free_all_paths(t_pipex *px);
void		free_pipes_memory(t_pipex *px);
void		cleanup_pipex(t_pipex *px);
void		error_exit(t_pipex *px, char *msg);
void		child_error_exit(t_pipex *px, char *msg);

void		handle_here_doc(t_pipex *px);
void		wait_for_all_children(t_pipex *px);
void		child_cmd_not_found(t_pipex *px, char *cmd);

#endif
