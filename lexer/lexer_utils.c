/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:20 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:35:02 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	skip_spaces(char **input)
{
	while (**input)
	{
		if (**input != ' ' && **input != '\t' && **input != '\n')
			return ;
		(*input)++;
	}
}

t_token	*match_and_or(char **input)
{
	if (**input == '&' && *(*input + 1) == '&')
	{
		*input += 2;
		return (create_token("&&", TOKEN_AND));
	}
	if (**input == '|' && *(*input + 1) == '|')
	{
		*input += 2;
		return (create_token("||", TOKEN_OR));
	}
	return (NULL);
}

t_token	*match_double_redirect(char **input)
{
	if (**input == '<' && *(*input + 1) == '<')
	{
		*input += 2;
		return (create_token("<<", TOKEN_HEREDOC));
	}
	if (**input == '>' && *(*input + 1) == '>')
	{
		*input += 2;
		return (create_token(">>", TOKEN_REDIRECT_APPEND));
	}
	return (NULL);
}

t_token	*detect_single_operator(char **input)
{
	t_token	*token;

	token = NULL;
	if (**input == '<')
		token = helper_create_token(input, "<", TOKEN_REDIRECT_IN);
	else if (**input == '>')
		token = helper_create_token(input, ">", TOKEN_REDIRECT_OUT);
	else if (**input == '(')
		token = helper_create_token(input, "(", TOKEN_LPAREN);
	else if (**input == ')')
		token = helper_create_token(input, ")", TOKEN_RPAREN);
	else if (**input == '|')
		token = helper_create_token(input, "|", TOKEN_PIPE);
	return (token);
}

t_token	*helper_create_token(char **input, char *value, t_token_type type)
{
	t_token	*token;

	token = NULL;
	if (input && *input && **input)
	{
		token = create_token(value, type);
		(*input)++;
	}
	return (token);
}
