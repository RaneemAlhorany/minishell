
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




