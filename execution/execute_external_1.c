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

static int	backup_std_fds(int *save_stdin, int *save_stdout, char **envp)
{
    *save_stdin = dup(STDIN_FILENO);
    *save_stdout = dup(STDOUT_FILENO);
    if (*save_stdin < 0 || *save_stdout < 0)
    {
        if (*save_stdin >= 0)
            close(*save_stdin);
        if (*save_stdout >= 0)
            close(*save_stdout);
        free_2D(envp);
        return (0);
    }
    return (1);
}

static int	prepare_external(t_cmd *cmd, t_shell *shell, char **envp,
        int saved[2])
{
    if (!backup_std_fds(&saved[0], &saved[1], envp))
        return (1);
    if (!apply_redirections(cmd->redirections, shell))
    {
        restore_fds(saved[0], saved[1]);
        free_2D(envp);
        return (1);
    }
    return (0);
}

static int	resolve_and_validate(t_cmd *cmd, t_shell *shell, char **envp,
        char **cmd_path)
{
    int	path_available;
    int	status;

    path_available = is_path_available(shell);
    *cmd_path = resolve_path_or_fail(cmd, shell, envp, path_available);
    if (!*cmd_path)
        return (127);
    status = validate_command_access(*cmd_path, cmd, envp);
    if (status != 0)
        return (status);
    return (0);
}

static int	run_external_and_cleanup(t_cmd *cmd, t_shell *shell,
        char *cmd_path, char **envp, int saved[2])
{
    pid_t	pid;

    pid = execute_with_fork(cmd, shell, cmd_path, envp);
    restore_fds(saved[0], saved[1]);
    free(cmd_path);
    free_2D(envp);
    if (pid < 0)
        return (1);
    return (wait_for_child(pid));
}

int execute_external(t_cmd *cmd, t_shell *shell)
{
    char    **envp;
    char    *cmd_path;
    int     status;
    int     saved[2];

    if (!is_valid_external_cmd(cmd, shell))
        return (127);
    envp = prepare_envp(shell);
    if (!envp)
        return (1);
    status = prepare_external(cmd, shell, envp, saved);
    if (status != 0)
        return (status);
    status = resolve_and_validate(cmd, shell, envp, &cmd_path);
    if (status != 0)
        return (restore_fds(saved[0], saved[1]), status);
    return (run_external_and_cleanup(cmd, shell, cmd_path, envp, saved));
}








