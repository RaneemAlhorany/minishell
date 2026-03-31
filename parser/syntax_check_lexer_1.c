#include "parsing.h"


int is_command_token(t_token_type type)
{
    if (type == TOKEN_WORD || is_redirection(type))
        return (1);
    return (0);
}



int is_redirection(t_token_type type)
{
    if (type == TOKEN_REDIRECT_IN
        ||type == TOKEN_REDIRECT_OUT
        || type == TOKEN_REDIRECT_APPEND
        || type == TOKEN_HEREDOC)
        return (1);

    return (0);
}

 int set_unexpected(char **unexpected_token, int *unexpected_newline,char *token_value, int is_newline)
{
    if (unexpected_token)
        *unexpected_token = token_value;
    if (unexpected_newline)
        *unexpected_newline = is_newline;
    return (0);
}

 int is_same_redir_char_token(t_token *token, char c)
{
    int i;

    if (!token || !is_redirection(token->type) || !token->value)
        return (0);
    i = 0;
    while (token->value[i])
    {
        if (token->value[i] != c)
            return (0);
        i++;
    }
    return (i > 0);
}

int redir_run_len(t_token *token, char c)
{
    int len;

    len = 0;
    while (token && is_same_redir_char_token(token, c))
    {
        len += ft_strlen(token->value);
        token = token->next;
    }
    return (len);
}
