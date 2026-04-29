/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:52 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:17 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_file_redirect(t_redirection *r, t_shell *shell, int flags,
		int std_fd)
{
	char	*filename;

	if (!prepare_redirect_file(r, shell, &filename))
		return (0);
	if (!redirect_fd(filename, flags, std_fd))
	{
		free(filename);
		return (0);
	}
	free(filename);
	return (1);
}

int	process_redirection(t_redirection *r, t_shell *shell, int saved_stdin)
{
	if (r->type == TOKEN_REDIRECT_IN)
		return (handle_file_redirect(r, shell, O_RDONLY, STDIN_FILENO));
	else if (r->type == TOKEN_REDIRECT_OUT)
		return (handle_file_redirect(r, shell, O_WRONLY | O_CREAT | O_TRUNC,
				STDOUT_FILENO));
	else if (r->type == TOKEN_REDIRECT_APPEND)
		return (handle_file_redirect(r, shell, O_WRONLY | O_CREAT | O_APPEND,
				STDOUT_FILENO));
	else if (r->type == TOKEN_HEREDOC)
		return (handle_heredoc_redct(r, shell, saved_stdin));
	return (1);
}

int	apply_redirections(t_redirection *r, t_shell *shell)
{
	int	saved_stdin;

	if (!r)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (0);
	while (r)
	{
		if (!process_redirection(r, shell, saved_stdin))
		{
			close(saved_stdin);
			return (0);
		}
		r = r->next;
	}
	close(saved_stdin);
	return (1);
}

int	handle_builtin_child(t_ast *n, t_shell *shell, t_builtin_type type)
{
	int			status;
	t_sigaction	old_sigpipe;
	t_sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGPIPE, &sa, &old_sigpipe);
	if (!apply_redirections(n->cmd->redirections, shell))
	{
		restore_sigpipe(&old_sigpipe);
		return (1);
	}
	status = execute_builtin(n->cmd, shell, type);
	restore_sigpipe(&old_sigpipe);
	return (status);
}

int	execute_builtin_with_redirect(t_ast *n, t_shell *shell, t_builtin_type type)
{
	int	save_stdin;
	int	save_stdout;
	int	status;

	if (shell && shell->in_child_process)
		return (handle_builtin_child(n, shell, type));
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdin < 0 || save_stdout < 0)
	{
		if (save_stdin >= 0)
			close(save_stdin);
		if (save_stdout >= 0)
			close(save_stdout);
		return (1);
	}
	if (!apply_redirections(n->cmd->redirections, shell))
	{
		restore_fds(save_stdin, save_stdout);
		return (1);
	}
	status = execute_builtin(n->cmd, shell, type);
	restore_fds(save_stdin, save_stdout);
	return (status);
}
