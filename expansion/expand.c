/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:50 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:23:56 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	handle_regular_char(t_expand *ex)
{
	if (ex->input[ex->i] == '\\' && ex->in_double)
	{
		ex->i++;
		if (ex->input[ex->i] && (ex->input[ex->i] == '"'
				|| ex->input[ex->i] == '$' || ex->input[ex->i] == '\\'))
		{
			if (!buffer_append_char(&ex->buf, ex->input[ex->i]))
				return (0);
			ex->i++;
			return (1);
		}
		if (!buffer_append_char(&ex->buf, '\\'))
			return (0);
		return (1);
	}
	if (!buffer_append_char(&ex->buf, ex->input[ex->i++]))
		return (0);
	return (1);
}

int	handle_expansion(t_expand *ex)
{
	char	*expanded;

	if (ex->input[ex->i] == '$' && !ex->in_single)
	{
		expanded = expand_var(ex->input, &ex->i, ex->env, ex->last_status);
		if (!expanded)
			return (0);
		if (!buffer_append_str(&ex->buf, expanded))
		{
			free(expanded);
			return (0);
		}
		free(expanded);
		return (1);
	}
	return (2);
}

int	handle_quotes(t_expand *ex)
{
	if (ex->input[ex->i] == '\'' && !ex->in_double)
	{
		ex->in_single = !ex->in_single;
		ex->i++;
		return (1);
	}
	if (ex->input[ex->i] == '"' && !ex->in_single)
	{
		ex->in_double = !ex->in_double;
		ex->i++;
		return (1);
	}
	return (2);
}

int	process_expand(t_expand *ex)
{
	int	status;

	while (ex->input[ex->i])
	{
		status = handle_quotes(ex);
		if (status == 1)
			continue ;
		status = handle_expansion(ex);
		if (status == 0)
			return (0);
		if (status == 1)
			continue ;
		if (!handle_regular_char(ex))
			return (0);
	}
	return (1);
}

char	*expand_string(char *input, t_env *env, int last_status)
{
	t_expand	ex;

	if (!init_expand(&ex, input, env, last_status))
		return (NULL);
	if (!process_expand(&ex))
	{
		free(ex.buf.data);
		return (NULL);
	}
	if (ex.in_single || ex.in_double)
	{
		free(ex.buf.data);
		return (NULL);
	}
	return (ex.buf.data);
}
