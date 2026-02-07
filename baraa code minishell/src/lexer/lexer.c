#include "minishell.h"



char	*get_string_until_quote(char *input, int *i, char quote)
{
	int		start;
	char	*result;
	size_t	len;

	if (!input)
		return (NULL);
	(*i)++;  // Move past the opening quote " or '
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	len = (size_t)(*i - start);
	if (input[*i] == quote)
		(*i)++;
	result = ft_substr(input, (unsigned int)start, len);
	return (result);
}

char	*get_word(char *input, int *i)
{
	int		start;
	size_t	len;
	char	*result;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i]) && !is_operator(input[*i]))
		(*i)++;
	len = (size_t)(*i - start);
	result = ft_substr(input, (unsigned int)start, len);
	return (result);
}

char	*get_operator(char *input, int *i, t_token_type *type)
{
	char	*op;

	if (input[*i] == '|')
	{
		*type = TOKEN_PIPE;
		op = ft_substr(input, (unsigned int)*i, 1);
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*type = TOKEN_HEREDOC;
			op = ft_substr(input, (unsigned int)*i, 2);
			*i += 2;
		}
		else
		{
			*type = TOKEN_REDIR_IN;
			op = ft_substr(input, (unsigned int)*i, 1);
			(*i)++;
		}
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			*type = TOKEN_REDIR_APPEND;
			op = ft_substr(input, (unsigned int)*i, 2);
			*i += 2;
		}
		else
		{
			*type = TOKEN_REDIR_OUT;
			op = ft_substr(input, (unsigned int)*i, 1);
			(*i)++;
		}
	}
	return (op);
}

t_token	*lexer(char *input)
{
	t_token			*head;
	t_token_type	type;
	char			*value;
	int				i;

	if (!input || !input[0])
		return (NULL);
	head = NULL;
	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		if (is_operator(input[i]))
		{
			type = TOKEN_WORD;
			value = get_operator(input, &i, &type);
			add_token(&head, create_token(type, value));
		}
		else if (input[i] == '"')
		{
			value = get_string_until_quote(input, &i, '"');
			add_token(&head, create_token(TOKEN_WORD, value));
		}
		else if (input[i] == '\'')
		{
			value = get_string_until_quote(input, &i, '\'');
			add_token(&head, create_token(TOKEN_WORD, value));
		}
		else
		{
			value = get_word(input, &i);
			add_token(&head, create_token(TOKEN_WORD, value));
		}
	}
	return (head);
}
