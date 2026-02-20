#include "tree.h"

t_ast *new_cmd_node(t_cmd *cmd)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = NODE_CMD;
    node->cmd = cmd;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

t_ast *new_pipe_node(t_ast *left, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = NODE_PIPE;
    node->cmd = NULL;
    node->left = left;
    node->right = right;
    return (node);
}

t_ast *build_ast_from_cmds(t_cmd *cmds)
{
    t_ast *left;
    t_cmd *next;

    if (!cmds)
        return (NULL);
    if (!cmds->next)
        return (new_cmd_node(cmds));
    next = cmds->next;
    cmds->next = NULL;
    left = new_cmd_node(cmds);
    return (new_pipe_node(left, build_ast_from_cmds(next)));
}
