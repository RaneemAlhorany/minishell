/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:51 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:09 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_deferred_echo(char **args, int index, t_shell *shell)
{
	char	*deferred;

	clear_prompt_prefix(shell);
	deferred = build_deferred_prompt_prefix(args, index);
	if (deferred)
	{
		shell->prompt_prefix = deferred;
		return (1);
	}
	return (0);
}

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

void	clear_prompt_prefix(t_shell *shell)
{
	if (shell->prompt_prefix)
	{
		free(shell->prompt_prefix);
		shell->prompt_prefix = NULL;
	}
}

int	builtin_echo(t_cmd *cmd, t_shell *shell)
{
	char	**args;
	int		index;
	int		n_flag;

	args = cmd->args;
	index = 1;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		clear_prompt_prefix(shell);
		return (0);
	}
	n_flag = parse_echo_options(args, &index);
	if (n_flag && cmd->redirections == NULL && isatty(STDOUT_FILENO))
	{
		if (handle_deferred_echo(args, index, shell))
			return (0);
	}
	print_echo_output(args, index, shell, n_flag);
	return (0);
}
