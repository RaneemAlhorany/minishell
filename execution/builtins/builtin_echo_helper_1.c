#include "builtin.h"




int	is_echo_option(const char *arg)
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



int	parse_echo_options(char **args, int *index)
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



void clear_prompt_prefix(t_shell *shell)
{
    if (shell->prompt_prefix)
    {
        free(shell->prompt_prefix);
        shell->prompt_prefix = NULL;
    }
}



 char *append_expanded(char *result, char *arg, t_shell *shell)
{
    char    *expanded;
    char    *tmp;

    expanded = expand_string(arg, shell->env, shell->last_exit_status);
    if (!expanded)
        expanded = arg;
    tmp = ft_strjoin(result, expanded);
    free(result);
    if (expanded != arg)
        free(expanded);
    return (tmp);
}

