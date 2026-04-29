/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:37 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:21:38 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include <signal.h>
# include <stddef.h>

typedef struct sigaction		t_sigaction;

typedef struct s_shell			t_shell;

extern volatile sig_atomic_t	g_last_signal;

// signals
void							handle_sigint_exec_mode(int signum);
void							handle_sigint_interactive(int signum);
void							set_interactive_readline_mode(int enabled);
void							setup_signals(void);

// signals_utils
void							heredoc_child_sigint(int signum);
void							setup_execution_signal(int interactive);
void							setup_child_signals(void);
void							handle_sigint(t_shell *shell);

#endif