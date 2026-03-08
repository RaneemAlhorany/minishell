// edit +test


#include "builtin.h"

int is_numeric(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);

    if (str[i] == '+' || str[i] == '-')
        i++;

    if (!str[i])
        return (0);

    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    int status;

    ft_putendl_fd("exit", 1);

    if (!cmd->args[1])
        exit(shell->last_exit_status);

    if (!is_numeric(cmd->args[1]))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(255);
    }

    if (cmd->args[2])
    {
        ft_putendl_fd("exit: too many arguments", 2);
        shell->last_exit_status = 1;
        return (1);
    }

    status = ft_atoi(cmd->args[1]);
    exit((unsigned char)status);
}

