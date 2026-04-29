/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:27 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:50 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wildcard_match(const char *pattern, const char *name)
{
	const char	*star;
	const char	*match;

	star = NULL;
	match = NULL;
	while (*name)
	{
		if (*pattern == '*')
			handle_star(&pattern, &star, &match, &name);
		else if (*pattern == *name)
		{
			(pattern)++;
			(name)++;
		}
		else if (star)
		{
			pattern = star + 1;
			match++;
			name = match;
		}
		else
			return (0);
	}
	return (skip_stars(pattern));
}

void	handle_star(const char **pattern, const char **star, const char **match,
		const char **name)
{
	*star = *pattern;
	*match = *name;
	(*pattern)++;
}

int	skip_stars(const char *pattern)
{
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

int	append_match(char ***arr, int *count, int *cap, char *name)
{
	if (*count >= *cap)
	{
		if (!resize_array(arr, cap, *count))
			return (0);
	}
	(*arr)[*count] = ft_strdup(name);
	if (!(*arr)[*count])
	{
		free_2d(*arr);
		return (0);
	}
	(*count)++;
	return (1);
}

int	resize_array(char ***arr, int *cap, int count)
{
	char	**new_arr;
	int		i;

	if (*cap == 0)
		*cap = 8;
	else
		*cap *= 2;
	new_arr = malloc(sizeof(char *) * (*cap));
	if (!new_arr)
		return (0);
	i = 0;
	while (i < count)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = new_arr;
	return (1);
}
