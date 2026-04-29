/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:28 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:26:27 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "../minishell.h"

void	heredoc_child_sigint(int signum)
{
	(void)signum;
	g_last_signal = SIGINT;
}

void	setup_execution_signal(int interactive)
{
	t_sigaction	sa_int;
	t_sigaction	sa_quit;

	if (interactive)
		sa_int.sa_handler = heredoc_child_sigint;
	else
		sa_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_child_signals(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint(t_shell *shell)
{
	if ((int)g_last_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		g_last_signal = 0;
	}
}
