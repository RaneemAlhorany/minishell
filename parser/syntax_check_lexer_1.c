/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_lexer_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:22 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:20:24 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_unexpected(char **unexpected_token, int *unexpected_newline,
		char *token_value, int is_newline)
{
	if (unexpected_token)
		*unexpected_token = token_value;
	if (unexpected_newline)
		*unexpected_newline = is_newline;
	return (0);
}

int	check_primary_syntax(t_token **tokens, char **unexpect_token,
		int *unexpect_line)
{
	if (!*tokens)
		return (set_unexpected(unexpect_token, unexpect_line, NULL, 1));
	if ((*tokens)->type == TOKEN_LPAREN)
	{
		*tokens = (*tokens)->next;
		if (!*tokens)
			return (set_unexpected(unexpect_token, unexpect_line, NULL, 1));
		if ((*tokens)->type == TOKEN_RPAREN)
			return (set_unexpected(unexpect_token, unexpect_line,
					(*tokens)->value, 0));
		if (!check_and_or_syntax(tokens, unexpect_token, unexpect_line))
			return (0);
		if (!*tokens)
			return (set_unexpected(unexpect_token, unexpect_line, NULL, 1));
		if ((*tokens)->type != TOKEN_RPAREN)
			return (set_unexpected(unexpect_token, unexpect_line,
					(*tokens)->value, 0));
		*tokens = (*tokens)->next;
		return (1);
	}
	if (!((*tokens)->type == TOKEN_WORD || is_redirection((*tokens)->type)
			|| (*tokens)->type == TOKEN_LPAREN))
		return (set_unexpected(unexpect_token, unexpect_line, (*tokens)->value,
				0));
	return (check_command_syntax(tokens, unexpect_token, unexpect_line));
}

int	check_pipe_syntax(t_token **tokens, char **unexpected_token,
		int *unexpected_newline)
{
	if (!check_primary_syntax(tokens, unexpected_token, unexpected_newline))
		return (0);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (!*tokens)
			return (set_unexpected(unexpected_token, unexpected_newline, NULL,
					1));
		if (!((*tokens)->type == TOKEN_WORD
				|| is_redirection((*tokens)->type)
				|| (*tokens)->type == TOKEN_LPAREN))
			return (set_unexpected(unexpected_token, unexpected_newline,
					(*tokens)->value, 0));
		if (!check_primary_syntax(tokens, unexpected_token, unexpected_newline))
			return (0);
	}
	return (1);
}

int	check_and_or_syntax(t_token **tokens, char **unexpected_token,
		int *unexpected_newline)
{
	if (!check_pipe_syntax(tokens, unexpected_token, unexpected_newline))
		return (0);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR) && (*tokens)->type != TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (!*tokens)
			return (set_unexpected(unexpected_token, unexpected_newline, NULL,
					1));
		if (!((*tokens)->type == TOKEN_WORD
				|| is_redirection((*tokens)->type)
				|| (*tokens)->type == TOKEN_LPAREN))
			return (set_unexpected(unexpected_token, unexpected_newline,
					(*tokens)->value, 0));
		if (!check_pipe_syntax(tokens, unexpected_token, unexpected_newline))
			return (0);
	}
	return (1);
}

int	syntax_check(t_token *head, char **unexpected_token,
		int *unexpected_newline)
{
	t_token	*current;

	if (unexpected_token)
		*unexpected_token = NULL;
	if (unexpected_newline)
		*unexpected_newline = 0;
	if (!head)
		return (0);
	current = head;
	if (!check_and_or_syntax(&current, unexpected_token, unexpected_newline))
		return (0);
	if (current)
		return (set_unexpected(unexpected_token, unexpected_newline,
				current->value, 0));
	return (1);
}
