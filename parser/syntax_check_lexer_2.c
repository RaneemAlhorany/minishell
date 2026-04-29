/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_lexer_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:27 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:25:32 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_command_syntax(t_token **tokens, char **unexpected_token,
		int *unexpected_newline)
{
	int	has_word_or_redir;

	has_word_or_redir = 0;
	while (*tokens && !is_command_delimiter((*tokens)->type))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			has_word_or_redir = 1;
			*tokens = (*tokens)->next;
		}
		else if (is_redirection((*tokens)->type))
		{
			has_word_or_redir = 1;
			if (!check_redirection_syntax(*tokens, unexpected_token,
					unexpected_newline))
				return (0);
			*tokens = (*tokens)->next->next;
		}
		else
			return (set_unexpected(unexpected_token, unexpected_newline,
					(*tokens)->value, 0));
	}
	return (has_word_or_redir);
}

int	check_redirection_syntax(t_token *current, char **unexpected_token,
		int *unexpected_newline)
{
	if (!current->next)
		return (set_unexpected(unexpected_token, unexpected_newline, NULL, 1));
	if (current->next->type != TOKEN_WORD)
	{
		if (is_redirection(current->next->type) && current->value
			&& current->next->value
			&& current->value[0] == current->next->value[0])
			return (set_redir_unexpected(current, unexpected_token,
					unexpected_newline));
		return (set_unexpected(unexpected_token, unexpected_newline,
				current->next->value, 0));
	}
	return (1);
}

int	set_redir_unexpected(t_token *current, char **unexpected_token,
		int *unexpected_newline)
{
	int		len;
	char	c;

	c = current->value[0];
	len = redir_run_len(current, c);
	if (c == '<')
	{
		if (len <= 3)
			return (set_unexpected(unexpected_token, unexpected_newline, NULL,
					1));
		if (len == 4)
			return (set_unexpected(unexpected_token, unexpected_newline, "<",
					0));
		if (len == 5)
			return (set_unexpected(unexpected_token, unexpected_newline, "<<",
					0));
		return (set_unexpected(unexpected_token, unexpected_newline, "<<<", 0));
	}
	if (len <= 2)
		return (set_unexpected(unexpected_token, unexpected_newline, NULL, 1));
	if (len == 3)
		return (set_unexpected(unexpected_token, unexpected_newline, ">", 0));
	return (set_unexpected(unexpected_token, unexpected_newline, ">>", 0));
}

int	redir_run_len(t_token *token, char c)
{
	int	len;

	len = 0;
	while (token && is_same_redir_char_token(token, c))
	{
		len += ft_strlen(token->value);
		token = token->next;
	}
	return (len);
}

int	is_same_redir_char_token(t_token *token, char c)
{
	int	i;

	if (!token || !is_redirection(token->type) || !token->value)
		return (0);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] != c)
			return (0);
		i++;
	}
	return (i > 0);
}
