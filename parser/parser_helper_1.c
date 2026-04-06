
#include "parsing.h"


int is_binary_operator(t_token_type type)
{
    if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR)
        return (1);
    return (0);
}


int is_command_delimiter(t_token_type type)
{
    if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
        || type == TOKEN_LPAREN || type == TOKEN_RPAREN)
        return (1);
    return (0);
}


void free_redirections(t_redirection *r)
{
    t_redirection *tmp;

    while (r)
    {
        tmp = r->next;
        free(r->filename);
        free(r);
        r = tmp;
    }
}


void free_command(t_cmd *cmd)
{
    int i;

    if (!cmd)
        return;

    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }
        free(cmd->args);
    }

    free_redirections(cmd->redirections);
    free(cmd);
}


void free_ast(t_ast *ast)
{
    if (!ast)
        return;

    if (ast->type == NODE_COMMAND)
    {
        free_command(ast->cmd);
    }
    else if (ast->type == NODE_PIPE || ast->type == NODE_AND
        || ast->type == NODE_OR || ast->type == NODE_GROUP)
    {
        free_ast(ast->pipe.left);
        free_ast(ast->pipe.right);
    }

    free(ast);
}
