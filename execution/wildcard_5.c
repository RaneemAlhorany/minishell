/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:38 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:33:27 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	copy_normal_arg(char **new_arg, int *j, char *arg)
{
	new_arg[*j] = ft_strdup(arg);
	if (!new_arg[*j])
		return (0);
	(*j)++;
	return (1);
}

int	handle_wildcard(char **new_arg, int *j, char *arg)
{
	char	**matches;
	int		match_count;

	if (!collect_matches(arg, &matches, &match_count))
		return (0);
	if (match_count == 0)
	{
		if (!copy_normal_arg(new_arg, j, arg))
			return (free_str_array(matches, match_count), 0);
	}
	else
	{
		if (!add_matches(new_arg, j, matches, match_count))
			return (free_str_array(matches, match_count), 0);
	}
	free_str_array(matches, match_count);
	return (1);
}

int	add_matches(char **new_args, int *j, char **matches, int match_count)
{
	int	k;

	k = 0;
	while (k < match_count)
	{
		new_args[*j] = ft_strdup(matches[k]);
		if (!new_args[*j])
			return (0);
		(*j)++;
		k++;
	}
	return (1);
}
