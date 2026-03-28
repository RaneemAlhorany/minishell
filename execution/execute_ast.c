#include "execution.h"




int execute_ast(t_ast *node , t_shell *shell)
{
    if (!node)
        return (0);

    if (node->type == NODE_COMMAND)
        return (execute_command_node(node, shell));
    if (node->type == NODE_PIPE)
        return (execute_pipe_node(node, shell));
    return (0);
}

