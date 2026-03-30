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


char *resolve_command_path(t_cmd *cmd, t_shell *shell)
{
    char *cmd_path;

    if (ft_strchr(cmd->args[0], '/'))
        cmd_path = ft_strdup(cmd->args[0]);
    else
        cmd_path = find_program_on_path(cmd->args[0], shell);
    return (cmd_path);
}




int handle_command_not_found(char *cmd_name, char *cmd_path, char **envp)
{
    if (cmd_path)
        free(cmd_path);
    free_2D(envp);
    if (cmd_name && *cmd_name)
    {
        ft_putstr_fd(cmd_name, 2);
        ft_putendl_fd(" :command not found", 2);
    }
    else
        ft_putendl_fd(" :command not found", 2);
    return (127);
}


