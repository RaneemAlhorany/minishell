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

static int set_unexpected(char **unexpected_token, int *unexpected_newline,
    char *token_value, int is_newline)
{
    if (unexpected_token)
        *unexpected_token = token_value;
    if (unexpected_newline)
        *unexpected_newline = is_newline;
    return (0);
}

static int is_same_redir_char_token(t_token *token, char c)
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

static int redir_run_len(t_token *token, char c)
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

static int set_redir_unexpected(t_token *current,
    char **unexpected_token, int *unexpected_newline)
{
    int     len;
    char    c;

    c = current->value[0];
    len = redir_run_len(current, c);
    if (c == '<')
    {
        if (len <= 3)
            return (set_unexpected(unexpected_token, unexpected_newline, NULL, 1));
        if (len == 4)
            return (set_unexpected(unexpected_token, unexpected_newline, "<", 0));
        if (len == 5)
            return (set_unexpected(unexpected_token, unexpected_newline, "<<", 0));
        return (set_unexpected(unexpected_token, unexpected_newline, "<<<", 0));
    }
    if (len <= 2)
        return (set_unexpected(unexpected_token, unexpected_newline, NULL, 1));
    if (len == 3)
        return (set_unexpected(unexpected_token, unexpected_newline, ">", 0));
    return (set_unexpected(unexpected_token, unexpected_newline, ">>", 0));
}

int syntax_check(t_token *head, char **unexpected_token, int *unexpected_newline)
{
    t_token *current;
    t_token *pre;

    if (unexpected_token)
        *unexpected_token = NULL;
    if (unexpected_newline)
        *unexpected_newline = 0;
    if (!head)
        return (0);
    pre = NULL ;
    current = head;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (current->next && current->next->type == TOKEN_PIPE)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        "||", 0));
            if (!pre)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        current->value, 0));
            if (!current->next)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        NULL, 1));
            if ( !is_command_token(pre->type) || !is_command_token(current->next->type))
                return (set_unexpected(unexpected_token, unexpected_newline,
                        current->next->value, 0));
        }
        else if (is_redirection(current->type))
        {
            if (!current-> next ||  current-> next -> type != TOKEN_WORD)
                return (set_redir_unexpected(current,
                        unexpected_token, unexpected_newline));
        }
        pre = current;
        current = current -> next;
    }
    return (1);
}





