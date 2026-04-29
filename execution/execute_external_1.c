/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:47 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:16:49 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	prepare_execut(t_cmd *cmd, t_shell *shell, char **path, int *is_mini)
{
	int	status;

	status = resolve_and_validate(cmd, shell, path);
	if (status != 0)
		return (status);
	*is_mini = is_minishell_command(*path)
		|| is_minishell_command(cmd->args[0]);
	if (*is_mini)
		setup_execution_signal(0);
	return (0);
}

int	run_execution(t_cmd *cmd, t_shell *shell, char **envp, int saved[2])
{
	char	*path;
	pid_t	pid;
	int		is_mini;
	int		result;

	path = NULL;
	is_mini = 0;
	pid = -1;
	result = prepare_execut(cmd, shell, &path, &is_mini);
	if (result == 0)
	{
		pid = execute_with_fork(cmd, shell, path, envp);
		result = finalize_and_wait(pid, is_mini);
	}
	restore_fds(saved[0], saved[1]);
	if (path)
		free(path);
	if (envp)
		free_2d(envp);
	return (result);
}

int	backup_std_fds(int *save_stdin, int *save_stdout, char **envp)
{
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	if (*save_stdin < 0 || *save_stdout < 0)
	{
		if (*save_stdin >= 0)
			close(*save_stdin);
		if (*save_stdout >= 0)
			close(*save_stdout);
		free_2d(envp);
		return (0);
	}
	return (1);
}

int	prepare_external(t_cmd *cmd, t_shell *shell, char **envp, int saved[2])
{
	if (!backup_std_fds(&saved[0], &saved[1], envp))
		return (1);
	if (!apply_redirections(cmd->redirections, shell))
	{
		restore_fds(saved[0], saved[1]);
		free_2d(envp);
		return (1);
	}
	return (0);
}

int	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	**envp;
	int		saved[2];
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0] || !shell)
		return (127);
	envp = env_list_to_envp(shell->env);
	if (!envp)
		status = 1;
	else
		status = prepare_external(cmd, shell, envp, saved);
	if (status)
		return (status);
	return (run_execution(cmd, shell, envp, saved));
}
