
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

//babo edit

int handle_command_not_found(char *cmd_name, char *cmd_path, char **envp)
{
    if (cmd_path)
        free(cmd_path);
    free_2D(envp);
    if (cmd_name && *cmd_name)
    {
        ft_putendl_fd(cmd_name, 2);
        ft_putendl_fd("command not found\n", 2);
    }
    else
        ft_putendl_fd("command not found\n", 2);
    return (127);
}

void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp , t_shell *shell)
{//babo edit
    setup_child_signals();
    if (!apply_redirections(cmd->redirections, shell))
    {
        free(cmd_path);
        free_2D(envp);
        _exit(1);
    }
    if (execve(cmd_path, cmd->args, envp) == -1)
    {
        perror(cmd->args[0]);
        _exit(127);
    }
}
//babo edit
int wait_for_child(pid_t pid)
{
    int status;
    int sig;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    sig = WTERMSIG(status);
    if (sig == SIGQUIT)
        write(STDERR_FILENO, "Quit (core dumped)\n", 19);
    return (128 + sig);
}


int execute_external(t_cmd *cmd, t_shell *shell)
{//babo edit
    pid_t   pid;
    char    *cmd_path;
    char    **envp;
    char    *path_value;
    int     path_available;

    if (!is_valid_external_cmd(cmd, shell))
        return (127);
    envp = env_list_to_envp(shell->env);
    if (!envp)
        return (1);

    path_value = get_env_value("PATH", shell->env);
    path_available = (path_value && *path_value);
    free(path_value);

    cmd_path = resolve_command_path(cmd, shell);
    if (!cmd_path)
    {
        if (!ft_strchr(cmd->args[0], '/') && !path_available)
        {
            errno = ENOENT;
            perror(cmd->args[0]);
            free_2D(envp);
            return (127);
        }
        return (handle_command_not_found(cmd->args[0], cmd_path, envp));
    }
    if (access(cmd_path, X_OK) != 0)
    {
        perror(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);
        if (errno == ENOENT)
            return (127);
        return (126);
    }
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
    free(cmd_path);
    free_2D(envp);
    return (wait_for_child(pid));
}

