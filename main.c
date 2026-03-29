#include "minishell.h"



int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_status;
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
	{
		ft_putendl_fd("minishell: initialization failed\n", 2);
		return (1);
	}
	setup_signals();
	shell_interactive(shell);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	rl_clear_history();
	return (exit_status);
}
