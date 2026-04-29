/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:33 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:31:48 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "../minishell.h"

volatile sig_atomic_t	g_last_signal = 0;

void	handle_sigint_exec_mode(int signum)
{
	(void)signum;
	g_last_signal = SIGINT;
	ft_putendl_fd("", STDOUT_FILENO);
}

void	handle_sigint_interactive(int signum)
{
	(void)signum;
	g_last_signal = SIGINT;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_interactive_readline_mode(int enabled)
{
	t_sigaction	sa_int;

	if (enabled)
		sa_int.sa_handler = handle_sigint_interactive;
	else
		sa_int.sa_handler = handle_sigint_exec_mode;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
}

void	setup_signals(void)
{
	t_sigaction	sa_quit;

	set_interactive_readline_mode(1);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
