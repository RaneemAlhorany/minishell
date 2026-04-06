#include "execution.h"



void	cleanup_child_state(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->active_tokens)
    {
        free_tokens(shell->active_tokens);
        shell->active_tokens = NULL;
    }
    if (shell->active_ast)
    {
        free_ast(shell->active_ast);
        shell->active_ast = NULL;
    }
    free_shell(shell);
    rl_clear_history();
}



void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp , t_shell *shell)
{
    setup_child_signals();
    if (!apply_redirections(cmd->redirections, shell))
    {
        free(cmd_path);
        free_2D(envp);
        cleanup_child_state(shell);
        _exit(1);
    }
    if (execve(cmd_path, cmd->args, envp) == -1)
    {
        perror(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);
        cleanup_child_state(shell);
        _exit(127);
    }
}


int wait_for_child(pid_t pid)
{
    int status;
    int sig;
    int i;

    i = waitpid(pid, &status, 0);
    while (i == -1 && errno == EINTR)
        i = waitpid(pid, &status, 0);
    if (i == -1)
        return (1);
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


