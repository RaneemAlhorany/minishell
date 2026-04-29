/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:13 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:17:15 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wait_for_pipe(pid_t left_pid, pid_t right_pid)
{
	int	right_status;
	int	sig;
	int	exit_code;

	right_status = 0;
	if (wait_loop(left_pid, right_pid, &right_status))
		return (1);
	sig = right_status & 0x7F;
	if (sig == 0)
	{
		exit_code = (right_status >> 8) & 0xFF;
		if (exit_code == 128 + SIGQUIT)
			g_last_signal = SIGQUIT;
		return (exit_code);
	}
	g_last_signal = sig;
	return (128 + sig);
}

int	wait_loop(pid_t left_pid, pid_t right_pid, int *right_status)
{
	int		status;
	int		reaped;
	pid_t	waited;

	reaped = 0;
	while (reaped < 2)
	{
		waited = waitpid(-1, &status, 0);
		if (waited == -1)
		{
			if (errno == EINTR)
				continue ;
			if (errno == ECHILD)
				break ;
			return (1);
		}
		if (waited == left_pid || waited == right_pid)
			reaped++;
		if (waited == right_pid)
			*right_status = status;
	}
	return (0);
}
