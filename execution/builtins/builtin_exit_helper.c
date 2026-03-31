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






int handle_no_args(t_shell *shell)
{
    shell->is_running = 0;
    return (shell->last_exit_status);
}

int handle_numeric_error(char *arg, char *trimmed, t_shell *shell)
{
    ft_putstr_fd("exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putendl_fd(": numeric argument required", 2);
    free(trimmed);
    shell->is_running = 0;
    return (2);
}


int handle_too_many_args(t_shell *shell, char *trimmed)
{
    ft_putendl_fd("exit: too many arguments", 2);
    shell->last_exit_status = 1;
    free(trimmed);
    return (1);
}

