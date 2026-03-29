#include "execution.h"



void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp , t_shell *shell)
{
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




char **prepare_envp(t_shell *shell)
{
    char **envp;

    envp = env_list_to_envp(shell->env);
    return (envp);
}


