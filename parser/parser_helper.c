
#include "parsing.h"


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
}


void free_ast(t_ast *ast)
{
    if (!ast)
        return;

    if (ast->type == NODE_COMMAND)
    {
        free_command(ast->cmd);
    }
    else if (ast->type == NODE_PIPE)
    {
        free_ast(ast->pipe.left);
        free_ast(ast->pipe.right);
    }

    free(ast);
}
