/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:48 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:41 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	prepare_redirect_file(t_redirection *r, t_shell *shell, char **resolved)
{
	char	*expanded;

	expanded = expand_string(r->filename, shell->env, shell->last_exit_status);
	if (!expanded)
		return (0);
	if (is_ambiguous_redirect(r, expanded))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(r->filename, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		free(expanded);
		return (0);
	}
	*resolved = expanded;
	return (1);
}

int	is_ambiguous_redirect(t_redirection *r, char *filename)
{
	int	i;

	if (r->quoted)
		return (0);
	if (!filename || !*filename)
		return (1);
	i = 0;
	while (filename[i])
	{
		if (filename[i] == ' ' || filename[i] == '\t' || filename[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	redirect_fd(char *filename, int flags, int std_fd)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(filename);
		return (0);
	}
	if (dup2(fd, std_fd) < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	handle_heredoc_redct(t_redirection *r, t_shell *shell, int saved_stdin)
{
	int	fd;

	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		return (0);
	if (r->heredoc_fd >= 0)
	{
		fd = r->heredoc_fd;
		r->heredoc_fd = -1;
	}
	else
		fd = handle_heredoc(r, shell);
	if (fd < 0)
		return (0);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

void	restore_sigpipe(t_sigaction *old_act)
{
	if (old_act)
		sigaction(SIGPIPE, old_act, NULL);
}
