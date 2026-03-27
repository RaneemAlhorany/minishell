#include "execution.h"


int is_valid_command(t_ast *node)
{
    if (!node || !node->cmd || !node->cmd->args || !node->cmd->args[0])
        return (0);
    return (1);
}


void restore_fds(int stdin_copy, int stdout_copy)
{
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
}


int execute_builtin_with_redirection(t_ast *node, t_shell *shell, t_builtin_type type)
{
    int status;
    int save_stdin;
    int save_stdout;

    save_stdin = dup(STDIN_FILENO);
    save_stdout = dup(STDOUT_FILENO);

    if (!apply_redirections(node->cmd->redirections, shell))
    {
        restore_fds(save_stdin, save_stdout);
        return (1);
    }

    status = execute_builtin(node->cmd, shell, type);
    restore_fds(save_stdin, save_stdout);
    return (status);
}

//babo edit
int execute_command_node(t_ast *node, t_shell *shell)
{
    t_builtin_type builtin_type;
    int save_stdin;
    int save_stdout;

    if (!node || !node->cmd)
        return (0);

    if (!node->cmd->args || !node->cmd->args[0])
    {
        save_stdin = dup(STDIN_FILENO);
        save_stdout = dup(STDOUT_FILENO);
        if (save_stdin < 0 || save_stdout < 0)
        {
            if (save_stdin >= 0)
                close(save_stdin);
            if (save_stdout >= 0)
                close(save_stdout);
            return (1);
        }
        if (!apply_redirections(node->cmd->redirections, shell))
        {
            restore_fds(save_stdin, save_stdout);
            return (1);
        }
        restore_fds(save_stdin, save_stdout);
        return (0);
    }

    builtin_type = get_builtin_type(node->cmd->args[0]);

    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin_with_redirection(node, shell, builtin_type));

    return (execute_external(node->cmd, shell));
}

