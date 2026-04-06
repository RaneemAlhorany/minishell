
#include "parsing.h"

int check_and_or_syntax(t_token **tokens, char **unexpected_token, int *unexpected_newline)
{
    t_token *current;

    if (!check_pipe_syntax(tokens, unexpected_token, unexpected_newline))
        return 0;
    while (*tokens && is_binary_operator((*tokens)->type) && (*tokens)->type != TOKEN_PIPE)
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

        if (!check_pipe_syntax(tokens, unexpected_token, unexpected_newline))
            return 0;
    }
    return 1;
}

int check_primary_syntax(t_token **tokens, char **unexpected_token, int *unexpected_newline)
{
    if (!*tokens)
        return set_unexpected(unexpected_token, unexpected_newline, NULL, 1);
    if ((*tokens)->type == TOKEN_LPAREN)
    {
        *tokens = (*tokens)->next;
        if (!*tokens)
            return set_unexpected(unexpected_token, unexpected_newline, NULL, 1);
        if ((*tokens)->type == TOKEN_RPAREN)
            return set_unexpected(unexpected_token, unexpected_newline, (*tokens)->value, 0);
        if (!check_and_or_syntax(tokens, unexpected_token, unexpected_newline))
            return 0;
        if (!*tokens)
            return set_unexpected(unexpected_token, unexpected_newline, NULL, 1);
        if ((*tokens)->type != TOKEN_RPAREN)
            return set_unexpected(unexpected_token, unexpected_newline, (*tokens)->value, 0);
        *tokens = (*tokens)->next;
        return 1;
    }
    if (!is_primary_start((*tokens)->type))
        return set_unexpected(unexpected_token, unexpected_newline, (*tokens)->value, 0);
    return check_command_syntax(tokens, unexpected_token, unexpected_newline);
}

void	init_syntax_flags(char **unexpected_token, int *unexpected_newline)
{
    if (unexpected_token)
        *unexpected_token = NULL;
    if (unexpected_newline)
        *unexpected_newline = 0;
}

int	syntax_check(t_token *head, char **unexpected_token, int *unexpected_newline)
{
    t_token	*current;

    init_syntax_flags(unexpected_token, unexpected_newline);
    if (!head)
        return (0);
    current = head;
    if (!check_and_or_syntax(&current, unexpected_token, unexpected_newline))
        return (0);
    if (current)
        return (set_unexpected(unexpected_token, unexpected_newline,
                current->value, 0));
    return (1);
}
