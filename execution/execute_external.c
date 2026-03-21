
#include "execution.h"


char *resolve_command_path(t_cmd *cmd, t_shell *shell)
{
    char *cmd_path;

    if (ft_strchr(cmd->args[0], '/'))
        cmd_path = ft_strdup(cmd->args[0]);
    else
        cmd_path = find_program_on_path(cmd->args[0], shell);
    return (cmd_path);
}



int handle_command_not_found(char *cmd_path, char **envp)
{
    if (cmd_path)
        free(cmd_path);
    free_envp(envp);
    perror(cmd->args[0]);
    return (127);
}

void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp)
{
    if (!apply_redirections(cmd->redirections))
    {
        free(cmd_path);
        free_envp(envp);
        _exit(1);
    }

    if (execve(cmd_path, cmd->args, envp) == -1)
    {
        perror(cmd->args[0]);
        _exit(127);
    }
}

int wait_for_child(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (128 + WTERMSIG(status));
}


int execute_external(t_cmd *cmd, t_shell *shell)
{
    pid_t   pid;
    char    *cmd_path;
    char    **envp;

    if (!is_valid_external_cmd(cmd, shell))
        return (127);
    envp = env_list_to_envp(shell->env);
    if (!envp)
        return (1);
    cmd_path = resolve_command_path(cmd, shell);
    if (!cmd_path || access(cmd_path, X_OK) != 0)
        return (handle_command_not_found(cmd_path, envp));
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(cmd_path);
        free_envp(envp);
        return (1);
    }
    if (pid == 0)
        execute_child_process(cmd, cmd_path, envp);
    free(cmd_path);
    free_envp(envp);
    return (wait_for_child(pid));
}

