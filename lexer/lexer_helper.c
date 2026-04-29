/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:10 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:35:00 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	move_through_word(char **input)
{
	while (**input)
	{
		if (**input == '\'' || **input == '"')
		{
			if (!handle_quotes_for_lexer(input))
				return (0);
		}
		else if (**input == ' ' || **input == '\t' || **input == '<'
			|| **input == '>' || **input == '|' || **input == '&'
			|| **input == '(' || **input == ')' || **input == '\n')
			break ;
		else
			(*input)++;
	}
	return (1);
}

int	handle_quotes_for_lexer(char **input)
{
	char	quote;

	quote = **input;
	(*input)++;
	while (**input && **input != quote)
	{
		if (quote == '"' && **input == '\\')
		{
			(*input)++;
			if (**input == '"' || **input == '\\' || **input == '$')
				(*input)++;
		}
		else
			(*input)++;
	}
	if (**input != quote)
		return (0);
	(*input)++;
	return (1);
}

t_token	*handle_lexer_error(t_token *head, char *input)
{
	char	unclosed_quote;

	unclosed_quote = check_unclosed_quotes(input);
	if (unclosed_quote)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(unclosed_quote, 2);
		ft_putendl_fd("'", 2);
	}
	free_tokens(head);
	return (NULL);
}

char	check_unclosed_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			if (!skip_quote_content(input, &i, quote))
				return (quote);
		}
		else
			i++;
	}
	return (0);
}

int	skip_quote_content(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		if (quote == '"' && input[*i] == '\\')
		{
			(*i)++;
			if (input[*i] == '"' || input[*i] == '\\' || input[*i] == '$')
				(*i)++;
		}
		else
			(*i)++;
	}
	if (!input[*i] || input[*i] != quote)
		return (0);
	(*i)++;
	return (1);
}
