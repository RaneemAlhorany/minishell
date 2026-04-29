/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:46 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:33:51 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*build_deferred_prompt_prefix(char **args, int index)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (args[index])
	{
		tmp = ft_strjoin(result, args[index]);
		free(result);
		result = tmp;
		if (!result)
			return (NULL);
		result = append_space_if_needed(result, args[index + 1] != NULL);
		if (!result)
			return (NULL);
		index++;
	}
	return (result);
}

char	*append_space_if_needed(char *result, int has_next)
{
	char	*tmp;

	if (!has_next)
		return (result);
	tmp = ft_strjoin(result, " ");
	free(result);
	return (tmp);
}

void	print_echo_output(char **args, int index, t_shell *shell, int n_flag)
{
	while (args[index])
	{
		ft_putstr_fd(args[index], 1);
		if (args[index + 1])
			ft_putchar_fd(' ', 1);
		index++;
	}
	if (!n_flag)
	{
		ft_putchar_fd('\n', 1);
		clear_prompt_prefix(shell);
	}
}
