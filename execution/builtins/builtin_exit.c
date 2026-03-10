// edit +test


#include "builtin.h"

int is_numeric(char *str)
{
    int i;
    char *trimmed;

    if (!str)
        return (0);

    // Remove surrounding quotes if present
    if ((str[0] == '"' && str[ft_strlen(str) - 1] == '"') ||
        (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
    {
        str[ft_strlen(str) - 1] = '\0';
        str++;
    }

    trimmed = ft_strtrim(str, " \t\n"); // Remove leading and trailing whitespace
    if (!trimmed || !*trimmed)
    {
        free(trimmed);
        return (0);
    }

    i = 0;
    if (trimmed[i] == '+' || trimmed[i] == '-')
        i++;

    while (trimmed[i])
    {
        if (!ft_isdigit(trimmed[i]))
        {
            free(trimmed);
            return (0);
        }
        i++;
    }

    free(trimmed);
    return (1);
}

int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    int status;
    char *trimmed;

    ft_putendl_fd("exit", 1);

    if (!cmd->args[1])
        exit(shell->last_exit_status);

    // Trim and clean the argument
    trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
    if (!trimmed || !is_numeric(trimmed))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        free(trimmed);
        exit(255);
    }

    if (cmd->args[2])
    {
        ft_putendl_fd("exit: too many arguments", 2);
        shell->last_exit_status = 1;
        free(trimmed);
        return (1);
    }

    status = ft_atoi(trimmed);
    free(trimmed);
    exit((unsigned char)status);
}

