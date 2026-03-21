
#include "builtin.h"

void print_args(char **args, int index, t_shell *shell)
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

    n_flag = parse_char_flag(args, &index , 'n');
    print_args(args, index, shell);

    if (!n_flag)
        ft_putchar_fd('\n', 1);

    return (0);
}


