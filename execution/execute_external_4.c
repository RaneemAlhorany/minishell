/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:08 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:26 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_with_fork(t_cmd *cmd, t_shell *shell, char *cmd_path, char **envp)
{
	pid_t	pid;
	int		fd;

	fd = 3;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		while (fd < 1024)
			close(fd++);
		if (execve(cmd_path, cmd->args, envp) == -1)
		{
			try_sh_fallback(cmd, cmd_path, envp);
			handle_exec_error(cmd, cmd_path, envp, shell);
		}
	}
	return (pid);
}

void	try_sh_fallback(t_cmd *cmd, char *cmd_path, char **envp)
{
	char	**sh_argv;

	if (errno == ENOEXEC)
	{
		sh_argv = build_sh_fallback_args(cmd, cmd_path);
		if (sh_argv)
		{
			execve("/bin/sh", sh_argv, envp);
			free(sh_argv);
		}
	}
}

char	**build_sh_fallback_args(t_cmd *cmd, char *cmd_path)
{
	int		argc;
	int		i;
	char	**sh_argv;

	argc = 0;
	while (cmd->args && cmd->args[argc])
		argc++;
	sh_argv = ft_calloc(argc + 2, sizeof(char *));
	if (!sh_argv)
		return (NULL);
	sh_argv[0] = "/bin/sh";
	sh_argv[1] = cmd_path;
	i = 1;
	while (i < argc)
	{
		sh_argv[i + 1] = cmd->args[i];
		i++;
	}
	sh_argv[argc + 1] = NULL;
	return (sh_argv);
}

void	handle_exec_error(t_cmd *cmd, char *cmd_path, char **envp,
		t_shell *shell)
{
	int	exec_status;

	ft_putstr_fd("minishell: ", 2);
	perror(cmd->args[0]);
	exec_status = 126;
	if (errno == ENOENT)
		exec_status = 127;
	free(cmd_path);
	free_2d(envp);
	if (shell)
	{
		free_parts(shell);
		free_shell(shell);
		rl_clear_history();
	}
	exit(exec_status);
}

int	finalize_and_wait(pid_t pid, int is_mini)
{
	int	status;
	int	wait_ret;
	int	exit_code;

	exit_code = 1;
	if (pid >= 0)
	{
		wait_ret = waitpid(pid, &status, 0);
		while (wait_ret == -1 && errno == EINTR)
			wait_ret = waitpid(pid, &status, 0);
		if (wait_ret != -1)
		{
			if ((status & 0x7F) == 0)
				exit_code = (status >> 8) & 0xFF;
			else
			{
				g_last_signal = status & 0x7F;
				exit_code = 128 + g_last_signal;
			}
		}
	}
	if (is_mini)
		set_interactive_readline_mode(1);
	return (exit_code);
}
