#include "minishell.h"

void	print_error(const char *msg)// not used it yet, but I saw it in a summary
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}