#include "builtin.h"

static int	is_echo_option(const char *arg)
{
    int	j;

    if (!arg || arg[0] != '-' || arg[1] == '\0')
        return (0);
    j = 1;
    while (arg[j])
    {
        if (arg[j] != 'n' && arg[j] != 'e' && arg[j] != 'E')
            return (0);
        j++;
    }
    return (1);
}

static int	parse_echo_options(char **args, int *index)
{
    int	j;
    int	n_flag;

    n_flag = 0;
    while (args[*index] && is_echo_option(args[*index]))
    {
        j = 1;
        while (args[*index][j])
        {
            if (args[*index][j] == 'n')
                n_flag = 1;
            j++;
        }
        (*index)++;
    }
    return (n_flag);
}

int	print_args(char **args, int index, t_shell *shell)
{
    char    *expanded;
    int     printed_len;

    printed_len = 0;
    while (args[index])
    {
        expanded = expand_string(args[index], shell->env, shell->last_exit_status);
        if (!expanded)
            expanded = args[index];
        ft_putstr_fd(expanded, 1);
        printed_len += ft_strlen(expanded);
        if (expanded != args[index])
            free(expanded);
        if (args[index + 1])
        {
            ft_putchar_fd(' ', 1);
            printed_len++;
        }
        index++;
    }
    return (printed_len);
}

int builtin_echo(t_cmd *cmd, t_shell *shell)
{
    char    **args;
    int     index;
    int     n_flag;
    int     printed_len;

    args = cmd->args;
    index = 1;
    shell->prompt_needs_newline = 0;
    if (!args[1])
    {
        ft_putchar_fd('\n', 1);
        return (0);
    }
    n_flag = parse_echo_options(args, &index);
    printed_len = print_args(args, index, shell);
    if (!n_flag)
        ft_putchar_fd('\n', 1);
    else if (printed_len > 0)
        shell->prompt_needs_newline = 1;
    return (0);
}
