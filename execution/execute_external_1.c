#include "execution.h"



int execute_with_fork(t_cmd *cmd, t_shell *shell, char **envp)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free_2D(envp);
        return (-1);
    }
    if (pid == 0)
        execute_child_process(cmd, envp, shell);

    return (pid);
}



int execute_external(t_cmd *cmd, t_shell *shell)
{
    char    **envp;
    pid_t   pid;

    if (!is_valid_external_cmd(cmd, shell))
        return (127);
    envp = prepare_envp(shell);
    if (!envp)
        return (1);
    pid = execute_with_fork(cmd, shell, envp);
    free_2D(envp);
    if (pid < 0)
        return (1);
    return (wait_for_child(pid));
}








