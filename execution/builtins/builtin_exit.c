#include "builtin.h"

int check_digits(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
    {
        if(!str[i+1])
           return(0);
        i++;
    }
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

char *remove_quotes(char *str)
{
    if (!str)
        return (NULL);
    if ((str[0] == '"' && str[ft_strlen(str) - 1] == '"') ||
        (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
    {
        str[ft_strlen(str) - 1] = '\0';
        return (str + 1);
    }
    return (str);
}

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



int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    int status;
    char *trimmed;

    if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
        ft_putendl_fd("exit", 1);
    if (!cmd->args[1])
    {
        shell->is_running = 0;
        return (shell->last_exit_status);
    }
    trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
    if (!trimmed || !is_numeric(trimmed)  )
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(cmd->args[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        free(trimmed);
        shell->is_running = 0;
        return (2);
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
    shell->is_running = 0;
    return ((unsigned char)status);
}
