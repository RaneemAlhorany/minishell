#include "builtin.h"



char *append_space_if_needed(char *result, int has_next)
{
    char *tmp;

    if (!has_next)
        return (result);
    tmp = ft_strjoin(result, " ");
    free(result);
    return (tmp);
}

char *build_deferred_prompt_prefix(char **args, int index, t_shell *shell)
{
    char *result;

    result = ft_strdup("");
    if (!result)
        return (NULL);
    while (args[index])
    {
        result = append_expanded(result, args[index], shell);
        if (!result)
            return (NULL);
        result = append_space_if_needed(result, args[index + 1] != NULL);
        if (!result)
            return (NULL);
        index++;
    }
    return (result);
}

int	handle_no_args_echo(t_shell *shell)
{
	ft_putchar_fd('\n', 1);
	clear_prompt_prefix(shell);
	return (0);
}

int	handle_deferred_echo(char **args, int index, t_shell *shell)
{
	char	*deferred;

	clear_prompt_prefix(shell);
	deferred = build_deferred_prompt_prefix(args, index, shell);
	if (deferred)
	{
		shell->prompt_prefix = deferred;
		return (1);
	}
	return (0);
}

void	print_echo_output(char **args, int index, t_shell *shell, int n_flag)
{
	print_args(args, index, shell);
	if (!n_flag)
	{
		ft_putchar_fd('\n', 1);
		clear_prompt_prefix(shell);
	}
}