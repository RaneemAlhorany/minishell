/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:43 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:17:44 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	heredoc_child(int fd[2], char *limiter, t_shell *shell, int quoted)
{
	int	interrupted;
	int	tty_fd;
	int	tmp_fd;

	g_last_signal = 0;
	tmp_fd = 3;
	setup_execution_signal(1);
	setup_child_stdin(&tty_fd, fd, limiter, shell);
	close(fd[0]);
	while (tmp_fd < 1024)
	{
		if (tmp_fd != fd[1])
			close(tmp_fd);
		tmp_fd++;
	}
	interrupted = heredoc_loop(fd[1], limiter, shell, quoted);
	close(fd[1]);
	free(limiter);
	free_parts(shell);
	free_shell(shell);
	if (interrupted)
		exit(130);
	exit(0);
}

int	fork_heredoc_child(int fd[2], char *limiter, t_shell *shell, int quoted)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		free(limiter);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(fd, limiter, shell, quoted);
	close(fd[1]);
	return (pid);
}

char	*strip_heredoc_quotes(const char *s)
{
	char	*result;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"')
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*prepare_limit(t_redirection *redirect, int *quoted)
{
	char	*limiter;

	if (redirect)
	{
		*quoted = redirect->quoted;
		limiter = strip_heredoc_quotes(redirect->filename);
	}
	else
	{
		*quoted = 0;
		limiter = NULL;
	}
	return (limiter);
}

int	handle_heredoc(t_redirection *redirect, t_shell *shell)
{
	int		fd[2];
	char	*limiter;
	int		quoted;
	int		pid;

	if (pipe(fd) < 0)
	{
		perror("minishell: pipe");
		return (-1);
	}
	g_last_signal = 0;
	limiter = prepare_limit(redirect, &quoted);
	if (!limiter)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	pid = fork_heredoc_child(fd, limiter, shell, quoted);
	if (pid < 0)
		return (pid);
	return (finalize_heredoc_parent(fd, limiter, pid));
}
