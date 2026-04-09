#include "execution.h"



int handle_command_execution(t_ast *node, t_shell *shell)
{
    t_builtin_type builtin_type;
    int            dot_status;

    if (!expand_cmd_wildcards(node->cmd))
        return (1);
    dot_status = handle_dot_command(node->cmd);
    if (dot_status != -1)
        return (dot_status);
    builtin_type = get_builtin_type(node->cmd->args[0]);
    if (builtin_type == BUILTIN_ENV && node->cmd->args[1])
        return (execute_external(node->cmd, shell));
    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin_with_redirection(node, shell, builtin_type));
    return (execute_external(node->cmd, shell));
}



int execute_command_node(t_ast *node, t_shell *shell)
{
    int assignment_status;

    if (!node || !node->cmd)
        return (0);

    if (!node->cmd->args || !node->cmd->args[0])
        return (handle_empty_command(node, shell));
    if (node->cmd->args[0][0] == '\0' && !node->cmd->args[1])
        return (handle_empty_command(node, shell));

    assignment_status = handle_assignment_only_command(node, shell);
    if (assignment_status != -1)
        return (assignment_status);

    return (handle_command_execution(node, shell));
}
