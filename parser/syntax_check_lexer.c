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
            if (!pre || !current-> next)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        current->value, !current->next));
            if (current->next->type == TOKEN_PIPE)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        "||", 0));
            if ( !is_command_token(pre->type) || !is_command_token(current->next->type))
                return (set_unexpected(unexpected_token, unexpected_newline,
                        current->next->value, 0));
        }
        else if (is_redirection(current->type))
        {
            if (!current-> next ||  current-> next -> type != TOKEN_WORD)
                return (set_unexpected(unexpected_token, unexpected_newline,
                        current->next ? current->next->value : NULL,
                        !current->next));
        }
        pre = current;
        current = current -> next;
    }
    return (1);
}





