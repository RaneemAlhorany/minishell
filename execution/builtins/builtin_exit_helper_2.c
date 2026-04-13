#include "builtin.h"

static int	is_non_empty_numeric(char *trimmed)
{
    if (!trimmed || !*trimmed)
        return (0);
    if (!check_digits(trimmed))
        return (0);
    return (1);
}


int is_numeric(char *str)
{
    char *trimmed;
    char *clean;

    if (!str)
        return (0);

    clean = remove_quotes(str);
    trimmed = ft_strtrim(clean, " \t\n");
	if (!is_non_empty_numeric(trimmed))
		return (free(trimmed), 0);
	free(trimmed);
	return (1);
}




void print_exit_if_interactive(void)
{
    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
        ft_putendl_fd("exit", 1);
}




int get_exit_status(char *trimmed, long long value, t_shell *shell)
{
    free(trimmed);
    shell->is_running = 0;
    return ((unsigned char)value);
}




int    check_overflow(unsigned long long res, int digit, int sign)
{
    if (sign == 1 && (res > ((unsigned long long)LLONG_MAX - digit) / 10))
        return (0);
    if (sign == -1 && res > ((unsigned long long)LLONG_MAX + 1ULL - digit) / 10)
        return (0);
    return (1);
}


int    ft_isspace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}
