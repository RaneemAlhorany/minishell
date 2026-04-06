#include "minishell.h"

void skip_spaces(char **input)
{
    while (**input)
    {
        if (**input != ' ' && **input  != '\t' && **input  != '\n' )
            return ;
        (*input)++;
    }
}



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


t_token *helper_create_token (char **input , char *value , t_token_type type)
{ 
    t_token *token;

    token = NULL;
    if (input || *input || **input )
    {
        token = create_token(value, type);
        (*input)++;
    }
    return(token);
}

t_token *operator_detection(char **input)
{
    t_token *token;

    token = detect_double_operator(input);
    if (token)
        return (token);
    return (detect_single_operator(input));
}
