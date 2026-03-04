
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
        write(1, args[index], ft_strlen(args[index]));
        if (args[index + 1])
            write(1, " ", 1);
        index++;
    }
}

int builtin_echo(t_cmd *cmd, t_shell *shell)
{
    char    **args;
    int     index;
    int     flag;

    (void)shell;
    args = cmd->args;

    if (!args[1])
    {
        write(1, "\n", 1);
        return (0);
    }

    flag = parse_n_flag(args, &index);
    print_echo_args(args, index);

    if (flag == 0)
        write(1, "\n", 1);

    return (0);
}