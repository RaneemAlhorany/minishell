#include "minishell.h"


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

int	move_through_word(char **input)
{
	while (**input)
	{
		if (**input == '\'' || **input == '"')
		{
			if (!handle_quotes_for_lexer(input))
				return (0);
		}
		else if (**input == ' ' || **input == '\t'
			|| **input == '<' || **input == '>'
            || **input == '|' || **input == '&'
            || **input == '(' || **input == ')'
            || **input == '\n')
			break;
		else
			(*input)++;
	}
	return (1);
}


t_token *word_detection(char **input)
{
    char    *start;
    char    *temp;
    t_token *token;
    int     length;

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


t_token *lexer(char *input)
{
    t_token *head;
    t_token *new;
    char	unclosed_quote;
    char	*original_input;

    head = NULL;
    original_input = input;
    while (*input)
    {
        skip_spaces(&input);
        if (!*input)
            break;
        if (*input == '#')
            break;
        new = operator_detection(&input);
        if (new)
            append_token(&head ,new);
        else 
        {
            new = word_detection(&input);
            if (new)
                append_token(&head ,new );
            else 
            {
                unclosed_quote = check_unclosed_quotes(original_input);
                if (unclosed_quote)
                {
                    ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
                    ft_putchar_fd(unclosed_quote, 2);
                    ft_putendl_fd("'", 2);
                }
                free_tokens(head);
                return (NULL);
            }
        }
    }
    return (head);
}




