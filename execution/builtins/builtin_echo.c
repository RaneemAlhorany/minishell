
#include "builtin.h"



int  parse_n_flag(char **args, int *index)
{
    int j;
    int flag;

    flag = 0;
    *index = 1;
    while (args[*index])
    {
        if (args[*index][0] != '-')
            break;
        if (args[*index][1] != 'n')
            break;
        j = 1;
        while (args[*index][j] == 'n')
            j++;

        if (args[*index][j] == '\0')
        {
            flag = 1;
            (*index)++;
        }
        else
            break;
    }
    return (flag);
}

void print_echo_args(char **args, int index)
{
    while (args[index])
    {
       ft_putstr_fd(args[index], 1);
        if (args[index + 1])
            ft_putchar_fd(' ' , 1);
        index++;
    }
}



int builtin_echo(t_cmd *cmd, t_shell *shell)
{
    char    **args = cmd->args;
    int     index = 1;
    int     flag = 0;
    char    *expanded;

    if (!args[1])
    {
        ft_putchar_fd('\n', 1);
        return (0);
    }
    flag = parse_n_flag(args, &index);
    while (args[index])
    {
        expanded = expand_string(args[index], shell->env, shell->last_exit_status);
        if (!expanded)
            expanded = args[index]; // fallback if expand_string fails
        ft_putstr_fd(expanded, 1);
        free(expanded);
        if (args[index + 1])
            ft_putchar_fd(' ', 1);
        index++;
    }
    if (!flag)
        ft_putchar_fd('\n', 1);
    return (0);
}


