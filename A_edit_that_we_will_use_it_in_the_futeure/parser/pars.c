
#include "minishell.h"

int syntax_check(t_token *head)
{
    t_token *current;
    t_token *pre;

    if (!head)
        return (0);
    pre = NULL ;
    current = head;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (!pre || !current-> next)
                return (0);
            if (pre -> type != TOKEN_WORD  || current-> next -> type != TOKEN_WORD)
                return (0);
        }
        else if (is_redirection(current->type) == 1)
        {
            if (!current-> next ||  current-> next -> type != TOKEN_WORD)
                return (0);
        }
        pre = current;
        current = current -> next;
    }
    return (1);
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
