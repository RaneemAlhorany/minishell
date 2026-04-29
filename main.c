/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:10:23 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:10:27 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
