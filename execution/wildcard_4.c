/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:32 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:08 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	flush_pending_line(t_wildcard *ctx, t_wildcard_read_state *state)
{
	if (state->line_len == 0)
		return (1);
	state->line[state->line_len] = '\0';
	if (match_pattern(ctx->pattern, state->line) && !append_match(ctx->matches,
			ctx->count, ctx->cap, state->line))
		return (0);
	state->line_len = 0;
	return (1);
}

int	wait_and_check(pid_t pid, int status, int ok)
{
	if (waitpid(pid, &status, 0) < 0)
		return (0);
	if (!ok)
		return (0);
	if ((status & 0x7F) != 0)
		return (0);
	if (((status >> 8) & 0xFF) != 0)
		return (0);
	return (1);
}

void	sort_match(char **matches, int count)
{
	int		i;
	int		j;
	char	*tmp;
	int		cmp;

	if (!matches || count <= 1)
		return ;
	i = 1;
	while (i < count)
	{
		tmp = matches[i];
		j = i - 1;
		while (j >= 0)
		{
			cmp = compare_match_names(matches[j], tmp);
			if (cmp <= 0)
				break ;
			matches[j + 1] = matches[j];
			j--;
		}
		matches[j + 1] = tmp;
		i++;
	}
}

int	compare_match_names(char *a, char *b)
{
	int				i;
	unsigned char	ca;
	unsigned char	cb;

	if (!a || !b)
		return (0);
	i = 0;
	while (a[i] && b[i])
	{
		ca = (unsigned char)ft_tolower(a[i]);
		cb = (unsigned char)ft_tolower(b[i]);
		if (ca != cb)
			return ((int)ca - (int)cb);
		i++;
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

int	process_args(char **args, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (!has_wildcard_chars(args[i]))
		{
			if (!copy_normal_arg(new_args, &j, args[i]))
			{
				free_str_array(new_args, j);
				return (0);
			}
		}
		else if (!handle_wildcard(new_args, &j, args[i]))
		{
			free_str_array(new_args, j);
			return (0);
		}
		i++;
	}
	new_args[j] = NULL;
	return (1);
}
