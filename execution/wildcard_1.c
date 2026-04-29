/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:16 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:18:18 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	collect_matches(const char *pattern, char ***matches, int *count)
{
	t_wildcard	ctx;
	int			cap;

	ctx.pattern = pattern;
	ctx.matches = matches;
	ctx.count = count;
	ctx.cap = &cap;
	*matches = NULL;
	*count = 0;
	cap = 0;
	if (!fill_matches_from_ls(&ctx))
		return (0);
	if (*count > 1)
		sort_match(*matches, *count);
	return (1);
}

int	count_matches_in_cwd(char *pattern)
{
	char	**matches;
	int		count;

	if (!collect_matches(pattern, &matches, &count))
		return (-1);
	free_str_array(matches, count);
	return (count);
}

int	has_wildcard_chars(char *arg)
{
	if (!arg)
		return (0);
	while (*arg)
	{
		if (*arg == '*')
			return (1);
		arg++;
	}
	return (0);
}

int	count_expanded_words(char **args)
{
	int	count;
	int	i;
	int	expanded;

	count = 0;
	i = 0;
	while (args && args[i])
	{
		if (!has_wildcard_chars(args[i]))
			expanded = 1;
		else
		{
			expanded = count_matches_in_cwd(args[i]);
			if (expanded == 0)
				expanded = 1;
		}
		if (expanded < 0)
			return (-1);
		count += expanded;
		i++;
	}
	return (count);
}

int	expand_cmd_wildcards(t_cmd *cmd)
{
	int		words;
	char	**new_args;

	if (!cmd || !cmd->args)
		return (1);
	words = count_expanded_words(cmd->args);
	if (words < 0)
		return (0);
	new_args = malloc(sizeof(char *) * (words + 1));
	if (!new_args)
		return (0);
	if (!process_args(cmd->args, new_args))
		return (0);
	free_2d(cmd->args);
	cmd->args = new_args;
	return (1);
}
