#include "minishell.h"




t_token *detect_double_operator(char **input)
{
    t_token *token;

    token = NULL;
    if (**input == '&' && *(*input + 1) == '&')
    {
        token = create_token("&&", TOKEN_AND);
        *input += 2;
    }
    else if (**input == '|' && *(*input + 1) == '|')
    {
        token = create_token("||", TOKEN_OR);
        *input += 2;
    }
    if (**input == '<' && *(*input + 1) == '<')
    {
        token = create_token("<<", TOKEN_HEREDOC);
        *input += 2;
    }
    else if (**input == '>' && *(*input + 1) == '>')
    {
        token = create_token(">>", TOKEN_REDIRECT_APPEND);
        *input += 2;
    }
    return (token);
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

// char	check_unclosed_quotes(char *input)
// {
// 	int	i;
// 	char	quote;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '"')
// 		{
// 			quote = input[i];
// 			i++;
// 			while (input[i] && input[i] != quote)
// 			{
// 				if (quote == '"' && input[i] == '\\')
// 				{
// 					i++;
// 					if (input[i] == '"' || input[i] == '\\' || input[i] == '$')
// 						i++;
// 				}
// 				else
// 					i++;
// 			}
// 			if (!input[i] || input[i] != quote)
// 				return (quote);
// 			i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (0);
// }
