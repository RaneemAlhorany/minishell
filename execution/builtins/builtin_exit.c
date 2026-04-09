#include "builtin.h"







int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    char *trimmed;
    long long value;

    print_exit_if_interactive();

    if (!cmd->args[1])
        return (handle_no_args(shell));

    trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
    if (!trimmed || !is_numeric(trimmed) || !parse_exit_argument(trimmed, &value))
        return (handle_numeric_error(cmd->args[1], trimmed, shell));

    if (cmd->args[2])
        return (handle_too_many_args(shell, trimmed));

    return (get_exit_status(trimmed, value, shell));
}

