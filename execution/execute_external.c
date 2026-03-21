




int execute_external(t_cmd *cmd, t_shell *shell)
{
    pid_t   pid;
    int     status;
    char    *cmd_path;
    char    **envp;

    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (127);
    envp = env_list_to_envp(shell->env);
    if (!envp)
        return (1);
    if (ft_strchr(cmd->args[0], '/'))
        cmd_path = ft_strdup(cmd->args[0]);
    else
        cmd_path = find_program_on_path(cmd->args[0], shell);

    if (!cmd_path || access(cmd_path, X_OK) != 0)
    {
        if (!cmd_path)
            (void)0;
        else
            free(cmd_path);
        free_envp(envp);
        write(2, "minishell: external command not found\n", 36);
        return (127);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(cmd_path);
        free_envp(envp);
        return (1);
    }
    if (pid == 0)
    {
        execve(cmd_path, cmd->args, envp);
        perror(cmd->args[0]);
        _exit(127);
    }
    waitpid(pid, &status, 0);

    free(cmd_path);
    free_envp(envp);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (128 + WTERMSIG(status));
}








