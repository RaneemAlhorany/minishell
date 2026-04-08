#include "execution.h"

int	handle_dot_command(t_cmd *cmd)
{
    if (ft_strncmp(cmd->args[0], ".", 2) != 0)
        return (-1);
    if (cmd->args[1])
        return (-1);
    ft_putendl_fd("minishell: .: filename argument required", 2);
    ft_putendl_fd(".: usage: . filename [arguments]", 2);
    return (2);
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

int handle_empty_command(t_ast *node, t_shell *shell)
{
    int save_stdin;
    int save_stdout;

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

    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin_with_redirection(node, shell, builtin_type));

    return (execute_external(node->cmd, shell));
}



int execute_command_node(t_ast *node, t_shell *shell)
{
    if (!node || !node->cmd)
        return (0);

    if (!node->cmd->args || !node->cmd->args[0])
        return (handle_empty_command(node, shell));
    if (node->cmd->args[0][0] == '\0' && !node->cmd->args[1])
        return (handle_empty_command(node, shell));

    return (handle_command_execution(node, shell));
}
