/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:24 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:35:05 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

t_token	*word_detection(char **input)
{
	char	*start;
	char	*temp;
	t_token	*token;
	int		length;

	start = *input;
	if (!move_through_word(input))
		return (NULL);
	length = *input - start;
	if (length <= 0)
		return (NULL);
	temp = ft_substr(start, 0, length);
	if (!temp)
		return (NULL);
	token = create_token(temp, TOKEN_WORD);
	free(temp);
	if (!token)
		return (NULL);
	return (token);
}

t_token	*operator_detection(char **input)
{
	t_token	*token;

	token = match_and_or(input);
	if (token)
		return (token);
	token = match_double_redirect(input);
	if (token)
		return (token);
	return (detect_single_operator(input));
}

int	process_token(char **input, t_token **head)
{
	t_token	*new;

	new = operator_detection(input);
	if (!new)
		new = word_detection(input);
	if (!new)
		return (0);
	append_token(head, new);
	return (1);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	char	*original_input;

	head = NULL;
	original_input = input;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input || *input == '#')
			break ;
		if (!process_token(&input, &head))
			return (handle_lexer_error(head, original_input));
	}
	return (head);
}
