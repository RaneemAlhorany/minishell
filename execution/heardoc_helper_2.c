/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:38 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:49 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_heredoc_eof(char *limiter)
{
	if ((int)g_last_signal == SIGINT)
		return (1);
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("", STDOUT_FILENO);
	if (limiter)
	{
		ft_putstr_fd("minishell: warning: here-document at ", 2);
		ft_putstr_fd("line 1 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putendl_fd("')", 2);
	}
	else
	{
		ft_putendl_fd("minishell: warning: here-document ", 2);
		ft_putstr_fd("at line 1 delimited by end-of-file", 2);
	}
	return (0);
}

void	process_heredoc_line(char *line, t_shell *shell, int write_fd,
		int quoted)
{
	char	*expanded_line;

	if (quoted)
	{
		ft_putendl_fd(line, write_fd);
		return ;
	}
	expanded_line = expand_string(line, shell->env, shell->last_exit_status);
	if (expanded_line)
	{
		ft_putendl_fd(expanded_line, write_fd);
		free(expanded_line);
	}
	else
		ft_putendl_fd("", write_fd);
}

int	finalize_heredoc_parent(int fd[2], char *limiter, int pid)
{
	int	status;

	if (!wait_heredoc_child(pid, &status))
	{
		close(fd[0]);
		free(limiter);
		return (-1);
	}
	free(limiter);
	return (handle_child_status(fd, status));
}

int	wait_heredoc_child(pid_t pid, int *status)
{
	t_sigaction	old_int;
	t_sigaction	old_quit;
	t_sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	sigaction(SIGINT, &ignore, &old_int);
	sigaction(SIGQUIT, &ignore, &old_quit);
	while (waitpid(pid, status, 0) < 0)
	{
		if (errno != EINTR)
		{
			sigaction(SIGINT, &old_int, NULL);
			sigaction(SIGQUIT, &old_quit, NULL);
			return (0);
		}
	}
	sigaction(SIGINT, &old_int, NULL);
	sigaction(SIGQUIT, &old_quit, NULL);
	return (1);
}

int	handle_child_status(int fd[2], int status)
{
	int	sig;
	int	exit_code;

	sig = status & 0x7F;
	exit_code = (status >> 8) & 0xFF;
	if ((sig != 0 && sig == SIGINT) || (sig == 0 && exit_code == 130))
	{
		if (isatty(STDIN_FILENO))
			ft_putendl_fd("", STDOUT_FILENO);
		g_last_signal = SIGINT;
		close(fd[0]);
		return (-2);
	}
	if (sig != 0 || exit_code != 0)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
