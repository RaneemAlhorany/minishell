#include "minishell.h"


t_ast *create_ast_node(t_node_type type)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    if (type == NODE_PIPE)
    {
        node->pipe.left = NULL;
        node->pipe.right = NULL;
    }
    else if (type == NODE_COMMAND)
    {
        node->cmd.args = NULL;
        node->cmd.redirections = NULL;
    }
    return (node);
}
t_ast *parse_pipeline(t_token **tokens)
{
    t_ast *left;

    if (!tokens || !*tokens)
        return (NULL);

    left = build_command(tokens);
    if (!left)
        return (NULL);

    if (!is_pipe(tokens))
        return (left);

    return (create_pipe_node(tokens, left));
}


int is_pipe(t_token **tokens)
{
    if (!*tokens)
        return (0);
    if ((*tokens)->type != TOKEN_PIPE)
        return (0);
    return (1);
}

t_ast *create_pipe_node(t_token **tokens, t_ast *left)
{
    t_ast *node;
    t_ast *right;

    *tokens = (*tokens)->next;
    if (!*tokens)
    {
        free_ast(left);
        return (NULL);
    }
    node = create_ast_node(NODE_PIPE);
    if (!node)
    {
        free_ast(left);
        return (NULL);
    }
    right = parse_pipeline(tokens);
    if (!right)
    {
        free_ast(left);
        free(node);
        return (NULL);
    }
    node->pipe.left = left;
    node->pipe.right = right;
    return (node);
}
