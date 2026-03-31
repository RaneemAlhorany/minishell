#include "builtin.h"



int is_numeric(char *str)
{
    char *trimmed;
    char *clean;

    if (!str)
        return (0);

    clean = remove_quotes(str);
    trimmed = ft_strtrim(clean, " \t\n");

    if (!trimmed || !*trimmed)
    {
        free(trimmed);
        return (0);
    }

    if (!check_digits(trimmed))
    {
        free(trimmed);
        return (0);
    }

    free(trimmed);
    return (1);
}


void print_exit_if_interactive(void)
{
    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
        ft_putendl_fd("exit", 1);
}



int get_exit_status(char *trimmed, t_shell *shell)
{
    int status;

    status = ft_atoi(trimmed);
    free(trimmed);
    shell->is_running = 0;
    return ((unsigned char)status);
}

int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    char *trimmed;

    print_exit_if_interactive();

    if (!cmd->args[1])
        return (handle_no_args(shell));

    trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
    if (!trimmed || !is_numeric(trimmed))
        return (handle_numeric_error(cmd->args[1], trimmed, shell));

    if (cmd->args[2])
        return (handle_too_many_args(shell, trimmed));

    return (get_exit_status(trimmed, shell));
}

