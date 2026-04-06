#include "parsing.h"

int	is_primary_start(t_token_type type)
{
    if (type == TOKEN_WORD || is_redirection(type) || type == TOKEN_LPAREN)
        return (1);
    return (0);
}

int	set_redir_unexpected(t_token *current, char **unexpected_token,int *unexpected_newline)
{
    int	len;
    char	c;

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

int	check_redirection_syntax(t_token *current, char **unexpected_token,int *unexpected_newline)
{
    if (!current->next)
        return (set_unexpected(unexpected_token, unexpected_newline, NULL, 1));
    if (current->next->type != TOKEN_WORD)
    {
        if (is_redirection(current->next->type)
            && current->value && current->next->value
            && current->value[0] == current->next->value[0])
            return (set_redir_unexpected(current, unexpected_token,
                    unexpected_newline));
        return (set_unexpected(unexpected_token, unexpected_newline,
                current->next->value, 0));
    }
    return (1);
}

int	check_command_syntax(t_token **tokens, char **unexpected_token,int *unexpected_newline)
{
    int	has_word_or_redir;

    has_word_or_redir = 0;
    while (*tokens && !is_command_delimiter((*tokens)->type))
    {
        if ((*tokens)->type == TOKEN_WORD)
        {
            has_word_or_redir = 1;
            *tokens = (*tokens)->next;
        }
        else if (is_redirection((*tokens)->type))
        {
            has_word_or_redir = 1;
            if (!check_redirection_syntax(*tokens, unexpected_token,
                    unexpected_newline))
                return (0);
            *tokens = (*tokens)->next->next;
        }
        else
            return (set_unexpected(unexpected_token, unexpected_newline,
                    (*tokens)->value, 0));
    }
    return (has_word_or_redir);
}

int check_pipe_syntax(t_token **tokens, char **unexpected_token, int *unexpected_newline)
{
    t_token *current;

    if (!check_primary_syntax(tokens, unexpected_token, unexpected_newline))
        return 0;
    while (*tokens && (*tokens)->type == TOKEN_PIPE)
    {
        *tokens = (*tokens)->next;
        if (*tokens)
            current = *tokens;
        else
            current = NULL;
        if (current)
        {
            if (!is_primary_start(current->type))
                return set_unexpected(unexpected_token, unexpected_newline, current->value, 0);
        }
        else
            return set_unexpected(unexpected_token, unexpected_newline, NULL, 1);
        if (!check_primary_syntax(tokens, unexpected_token, unexpected_newline))
            return 0;
    }
    return 1;
}

