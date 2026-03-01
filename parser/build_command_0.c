

#include "parsing.h"



int process_word(t_ast *node, t_token **tokens)
{
    int index;

    index = count_args(node->cmd.args); 

    if (!handle_word_token(&node->cmd, *tokens, &index))
        return (0);

    *tokens = (*tokens)->next;
    return (1);
}


int process_redirection(t_ast *node, t_token **tokens)
{
    t_redirection *last;

    last = get_last_redirection(node->cmd.redirections);

    if (!handle_redirection_token(&node->cmd, tokens, &last))
        return (0);

    return (1);
}



int process_single_token(t_ast *node, t_token **tokens)
{
    if ((*tokens)->type == TOKEN_WORD)
        return (process_word(node, tokens));
    else if (is_redirection((*tokens)->type))
        return (process_redirection(node, tokens));
    else
        return (0);
}


int fill_command_data(t_ast *node, t_token **tokens)
{
    while (*tokens && (*tokens)->type != TOKEN_PIPE)
    {
        if (!process_single_token(node, tokens))
            return (0);
    }

    if (!node->cmd.args && !node->cmd.redirections)
        return (0);

    return (1);
}
