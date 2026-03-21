
#include "builtin.h"

void print_args(char **args, int index, t_shell *shell)
<<<<<<< HEAD
{
    char *expanded;

    while (args[index])
    {
        expanded = expand_string(args[index], shell->env, shell->last_exit_status);
        if (!expanded)
            expanded = args[index];
        ft_putstr_fd(expanded, 1);
        if (expanded != args[index])
            free(expanded);
        if (args[index + 1])
            ft_putchar_fd(' ', 1);
        index++;
    }
}

int  parse_n_flag(char **args, int *index)
=======
>>>>>>> 5b98786 (built in)
{
    char *expanded;

<<<<<<< HEAD
    flag = 0;
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

=======
    while (args[index])
    {
        expanded = expand_string(args[index], shell->env, shell->last_exit_status);
        if (!expanded)
            expanded = args[index];
        ft_putstr_fd(expanded, 1);
        if (expanded != args[index])
            free(expanded);
        if (args[index + 1])
            ft_putchar_fd(' ', 1);
        index++;
    }
}


>>>>>>> 5b98786 (built in)
int builtin_echo(t_cmd *cmd, t_shell *shell)
{
    char **args;
    int index;
    int n_flag;

    args = cmd->args;
    index = 1;

    if (!args[1])
    {
        ft_putchar_fd('\n', 1);
        return (0);
    }

<<<<<<< HEAD
    n_flag = parse_n_flag(args, &index);
=======
    n_flag = parse_char_flag(args, &index , 'n');
>>>>>>> 5b98786 (built in)
    print_args(args, index, shell);

    if (!n_flag)
        ft_putchar_fd('\n', 1);

    return (0);
}


