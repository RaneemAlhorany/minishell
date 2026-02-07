#include "minishell.h"

void skip_spaces(char **input)
{
    while (**input)
    {
        if (**input != ' ' && **input  != '\t')
            return ;
        (*input)++;
    }
}


t_token *detect_double_operator(char **input)
{
    t_token *token;

    token = NULL;
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
    {
        token = create_token("<", TOKEN_REDIRECT_IN);
        (*input)++;
    }
    else if (**input == '>')
    {
        token = create_token(">", TOKEN_REDIRECT_OUT);
        (*input)++;
    }
    else if (**input == '|')
    {
        token = create_token("|", TOKEN_PIPE);
        (*input)++;
    }
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

