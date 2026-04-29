/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:04 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:16:06 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	consume_char_flag(char *arg, int *flag, char character)
{
	int	j;

	j = 1;
	while (arg[j] == character)
		j++;
	if (arg[j] != '\0')
		return (0);
	*flag = 1;
	return (1);
}

int	is_matching_flag_arg(char *arg, char character)
{
	if (arg[0] != '-')
		return (0);
	if (arg[1] != character)
		return (0);
	return (1);
}

int	parse_char_flag(char **args, int *index, char character)
{
	int	flag;

	flag = 0;
	while (args[*index])
	{
		if (!is_matching_flag_arg(args[*index], character))
			break ;
		if (!consume_char_flag(args[*index], &flag, character))
			break ;
		(*index)++;
	}
	return (flag);
}

int	handle_unset_option(t_cmd *cmd, int *i)
{
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		if (parse_char_flag(cmd->args, i, 'v'))
			*i = 2;
		else
		{
			ft_putendl_fd("unset:invalid option", 2);
			ft_putendl_fd("unset: usage: unset [-v] [name ...]", 2);
			return (1);
		}
	}
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !shell)
		return (1);
	i = 1;
	if (handle_unset_option(cmd, &i))
		return (1);
	process_unset_args(cmd, shell, i);
	return (0);
}
