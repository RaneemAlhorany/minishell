#include "minishell.h"


int  move_through_word(char **input)
{
    char quote;

    while (**input)
    {
        if (**input == '\'' || **input == '"')
        {
            quote = **input;
            (*input)++;

            while (**input && **input != quote)
                (*input)++;

            if (**input != quote)
                return (0);

            (*input)++;
        }
        else if (**input == ' ' || **input == '\t'
            || **input == '<' || **input == '>'
            || **input == '|')
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
    temp = ft_substr(start, 0, length);
    if (!temp)
        return (NULL);

    token = create_token(temp, TOKEN_WORD);
    if (!token)
        return (NULL);

    return (token);
}


t_token *lexer (char *input)
{
    t_token *head;
    t_token *new;

    head = NULL;
    while (*input)
    {
        skip_spaces(&input);
        new = operator_detection(&input);
        if (new)
            append_token(&head ,new);
        else 
        {
            new = word_detection(&input);
            if (new)
                append_token(&head ,new );
            else 
                return (NULL);
        }
    }

    return (head);
}






