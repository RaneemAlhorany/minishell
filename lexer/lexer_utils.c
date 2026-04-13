#include "minishell.h"

static t_token	*match_and_or(char **input)
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

static t_token	*match_double_redirect(char **input)
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




t_token *detect_double_operator(char **input)
{
	t_token	*token;

	token = match_and_or(input);
	if (token)
		return (token);
	return (match_double_redirect(input));
}

t_token *detect_single_operator(char **input)
{
    t_token *token;

    token = NULL;
    if (**input == '<')
        token = helper_create_token( input ,"<", TOKEN_REDIRECT_IN);
    else if (**input == '>')
        token =  helper_create_token( input ,">", TOKEN_REDIRECT_OUT);
    else if (**input == '(')
        token =  helper_create_token( input ,"(", TOKEN_LPAREN);
    else if (**input == ')')
        token =  helper_create_token( input ,")", TOKEN_RPAREN);
    else if (**input == '|')
        token =  helper_create_token( input ,"|", TOKEN_PIPE);
    return (token);
}



t_token *operator_detection(char **input)
{
    t_token *token;

    token = detect_double_operator(input);
    if (token)
        return (token);
    return (detect_single_operator(input));
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

