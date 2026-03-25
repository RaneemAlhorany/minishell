
#ifndef SIGNALS_H
# define SIGNALS_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include <signal.h>
# include <stddef.h>

typedef struct sigaction	t_sigaction;

extern volatile sig_atomic_t	g_last_signal;


void handle_sigint_interactive(int signum);
void setup_signals(void);
void setup_child_signals(void);
void set_interactive_readline_mode(int enabled);
void handle_sigint_exec_mode(int signum);
int get_last_signal(void);
void clear_last_signal(void);


#endif