/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:05:56 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/28 14:53:01 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(t_pipex *px, char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;
	char	*cmd_name;

	if (!cmd || ft_strlen(cmd) == 0)
		child_error_exit(px, "Error: empty command");
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		child_error_exit(px, "split cmd args");
	cmd_path = find_cmd_path(cmd_args[0], px->envp);
	if (!cmd_path)
	{
		cmd_name = ft_strdup(cmd_args[0]);
		free_cmds(cmd_args);
		child_cmd_not_found(px, cmd_name);
	}
	execve(cmd_path, cmd_args, px->envp);
	perror(cmd_args[0]);
	free(cmd_path);
	free_cmds(cmd_args);
	child_error_exit(px, NULL);
}

void	setup_child_at_index(t_pipex *px, int i)
{
	if (i == 0)
	{
		if (dup2(px->infile_fd, STDIN_FILENO) == -1)
			child_error_exit(px, NULL);
	}
	else if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
		child_error_exit(px, NULL);
	if (i == px->cmd_count - 1)
	{
		if (dup2(px->outfile_fd, STDOUT_FILENO) == -1)
			child_error_exit(px, NULL);
	}
	else if (dup2(px->pipes[i][1], STDOUT_FILENO) == -1)
		child_error_exit(px, NULL);
	close_pipes(px);
	close_files(px);
	execute_cmd(px, px->cmds[i]);
}

pid_t	safe_fork(t_pipex *px)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit(px, "fork");
	return (pid);
}

void	create_pipes(t_pipex *px)
{
	int	i;

	px->pipes = ft_calloc(px->cmd_count - 1, sizeof(int *));
	if (!px->pipes)
		error_exit(px, "malloc pipes");
	i = 0;
	while (i < px->cmd_count - 1)
	{
		px->pipes[i] = malloc(sizeof(int) * 2);
		if (!px->pipes[i])
			error_exit(px, "malloc pipe");
		px->pipes[i][0] = -1;
		px->pipes[i][1] = -1;
		if (pipe(px->pipes[i]) == -1)
			error_exit(px, "pipe");
		i++;
	}
}

void	create_pipe_and_fork(t_pipex *px)
{
	int	i;

	create_pipes(px);
	px->pids = malloc(sizeof(pid_t) * px->cmd_count);
	if (!px->pids)
		error_exit(px, "malloc pids");
	i = 0;
	while (i < px->cmd_count)
	{
		px->pids[i] = safe_fork(px);
		if (px->pids[i] == 0)
			setup_child_at_index(px, i);
		i++;
	}
	close_pipes(px);
	close_files(px);
	wait_for_all_children(px);
	if (px->pids)
	{
		free(px->pids);
		px->pids = NULL;
	}
}
