
#include "builtin.h"



int	builtin_echo(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		index;
	int		n_flag;

	args = cmd->args;
	index = 1;

	if (!args[1])
		return (handle_no_args_echo(shell));

	n_flag = parse_echo_options(args, &index);

	if (n_flag && cmd->redirections == NULL && isatty(STDOUT_FILENO))
	{
		if (handle_deferred_echo(args, index, shell))
			return (0);
	}

	print_echo_output(args, index, shell, n_flag);
	return (0);
}





// char *build_deferred_prompt_prefix(char **args, int index, t_shell *shell)
// {
//     char    *expanded;
//     char    *tmp;
//     char    *result;

//     result = ft_strdup("");
//     if (!result)
//         return (NULL);
//     while (args[index])
//     {
//         expanded = expand_string(args[index], shell->env, shell->last_exit_status);
//         if (!expanded)
//             expanded = args[index];
//         tmp = ft_strjoin(result, expanded);
//         free(result);
//         if (expanded != args[index])
//             free(expanded);
//         if (!tmp)
//             return (NULL);
//         result = tmp;
//         if (args[index + 1])
//         {
//             tmp = ft_strjoin(result, " ");
//             free(result);
//             if (!tmp)
//                 return (NULL);
//             result = tmp;
//         }
//         index++;
//     }
//     return (result);
// }





// int builtin_echo(t_cmd *cmd, t_shell *shell)
// {
//     char **args;
//     int index;
//     int n_flag;

//     args = cmd->args;
//     index = 1;

//     if (!args[1])
//     {
//         ft_putchar_fd('\n', 1);
//         clear_prompt_prefix(shell);
//         return (0);
//     }

//     n_flag = parse_echo_options(args, &index);
//     if (n_flag && cmd->redirections == NULL && isatty(STDOUT_FILENO))
//     {
//         char *deferred;

//         clear_prompt_prefix(shell);
//         deferred = build_deferred_prompt_prefix(args, index, shell);
//         if (deferred)
//         {
//             shell->prompt_prefix = deferred;
//             return (0);
//         }
//         print_args(args, index, shell);
//         return (0);
//     }
//     print_args(args, index, shell);

//     if (!n_flag)
//     {
//         ft_putchar_fd('\n', 1);
//         clear_prompt_prefix(shell);
//     }
//     return (0);
// }


