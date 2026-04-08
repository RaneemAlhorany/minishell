#include "execution.h"

void	print_cmd_errno(const char *cmd_name)
{
    ft_putstr_fd("minishell: ", 2);
    perror(cmd_name);
}

void	print_is_directory(const char *cmd_name)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd((char *)cmd_name, 2);
    ft_putendl_fd(": Is a directory", 2);
}



int is_path_available(t_shell *shell)
{
    char *path_value;
    int  available;

    path_value = get_env_value("PATH", shell->env);
    available = (path_value && *path_value);
    free(path_value);
    return (available);
}




char *resolve_path_or_fail(t_cmd *cmd, t_shell *shell,char **envp, int path_available)
{
    char *cmd_path;

    cmd_path = resolve_command_path(cmd, shell);
    if (!cmd_path)
    {
        if (!ft_strchr(cmd->args[0], '/') && !path_available)
        {
            errno = ENOENT;
            print_cmd_errno(cmd->args[0]);
            free_2D(envp);
            return (NULL);
        }
        handle_command_not_found(cmd->args[0], cmd_path, envp);
        return (NULL);
    }
    return (cmd_path);
}


int validate_command_access(char *cmd_path, t_cmd *cmd, char **envp)
{
    struct stat st;

    if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        print_is_directory(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);
        return (126);
    }
    if (access(cmd_path, X_OK) != 0)
    {
        print_cmd_errno(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);

        if (errno == ENOENT)
            return (127);
        return (126);
    }
    return (0);
}



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








