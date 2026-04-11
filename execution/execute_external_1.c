#include "execution.h"



int execute_with_fork(t_cmd *cmd, t_shell *shell,char *cmd_path, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(cmd_path);
        free_2D(envp);
        return (1);
    }
    if (pid == 0)
        execute_child_process(cmd, cmd_path, envp, shell);

    return (pid);
}



int execute_external(t_cmd *cmd, t_shell *shell)
{
    char    **envp;
    char    *cmd_path;
    int     path_available;
    int     status;
    pid_t   pid;

    if (!is_valid_external_cmd(cmd, shell))
        return (127);
    envp = prepare_envp(shell);
    if (!envp)
        return (1);
    path_available = is_path_available(shell);
    cmd_path = resolve_path_or_fail(cmd, shell, envp, path_available);
    if (!cmd_path)
        return (127);
    status = validate_command_access(cmd_path, cmd, envp);
    if (status != 0)
        return (status);
    pid = execute_with_fork(cmd, shell, cmd_path, envp);
    free(cmd_path);
    free_2D(envp);
    if (pid < 0)
        return (1);
    return (wait_for_child(pid));
}








