#include "signals.h"

void	setup_child_signals(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_DFL; // استرجاع behavior الافتراضي
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}



// موجودين اضافه على الmain عارف انه مش كامل بس برضه لازم هيك تكون نتاج ال سقنل 
int	get_last_signal(void)
{
	return ((int)g_last_signal);
}
void	clear_last_signal(void)
{
	g_last_signal = 0;
}