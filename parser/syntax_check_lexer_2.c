#include "parsing.h"


int set_redir_unexpected(t_token *current,char **unexpected_token, int *unexpected_newline)
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



/////
void init_syntax_flags(char **unexpected_token, int *unexpected_newline)
{
    if (unexpected_token)
        *unexpected_token = NULL;
    if (unexpected_newline)
        *unexpected_newline = 0;
}


int check_pipe_syntax(t_token *current, t_token *pre,char **unexpected_token, int *unexpected_newline)
{
    if (current->next && current->next->type == TOKEN_PIPE)
        return (set_unexpected(unexpected_token, unexpected_newline, "||", 0));

    if (!pre)
        return (set_unexpected(unexpected_token, unexpected_newline,
                current->value, 0));

    if (!current->next)
        return (set_unexpected(unexpected_token, unexpected_newline,
                NULL, 1));

    if (!is_command_token(pre->type)
        || !is_command_token(current->next->type))
        return (set_unexpected(unexpected_token, unexpected_newline,
                current->next->value, 0));

    return (1);
}


int check_redirection_syntax(t_token *current,char **unexpected_token, int *unexpected_newline)
{
    if (!current->next || current->next->type != TOKEN_WORD)
        return (set_redir_unexpected(current,
                unexpected_token, unexpected_newline));
    return (1);
}

int syntax_check(t_token *head, char **unexpected_token, int *unexpected_newline)
{
    t_token *current;
    t_token *pre;

    init_syntax_flags(unexpected_token, unexpected_newline);
    if (!head)
        return (0);
    current = head;
    pre = NULL;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (!check_pipe_syntax(current, pre,unexpected_token, unexpected_newline))
                return (0);
        }
        else if (is_redirection(current->type))
        {
            if (!check_redirection_syntax(current,unexpected_token, unexpected_newline))
                return (0);
        }
        pre = current;
        current = current->next;
    }
    return (1);
}






