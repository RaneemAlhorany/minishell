
#include "execution.h"

void	setup_pipeline_wrapper_signals(void)
{
    t_sigaction	sa_int;
    t_sigaction	sa_quit;

    sa_int.sa_handler = SIG_IGN;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}


int is_valid_pipe_node(t_ast *node)
{
    if (!node || node->type != NODE_PIPE
        || !node->pipe.left || !node->pipe.right)
        return (0);
    return (1);
}

void execute_left_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    int status;

    setup_pipeline_wrapper_signals();
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    status = execute_ast(node->pipe.left, shell);
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
    else
        free_ast(node);
    free_shell(shell);
    rl_clear_history();
    _exit(status);
}



void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    int status;

    setup_pipeline_wrapper_signals();
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    status = execute_ast(node->pipe.right, shell);
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
    else
        free_ast(node);
    free_shell(shell);
    rl_clear_history();
    _exit(status);
}

int wait_for_pipe(pid_t left_pid, pid_t right_pid)
{
    int status;
    int i;

    while (waitpid(left_pid, NULL, 0) == -1)
    {
        if (errno != EINTR)
            break;
    }
    i = waitpid(right_pid, &status, 0);
    while (i == -1 && errno == EINTR)
        i = waitpid(right_pid, &status, 0);
    if (i == -1)
        return (1);
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 128 + SIGQUIT)
            g_last_signal = SIGQUIT;
        return (WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
        g_last_signal = WTERMSIG(status);
        return (128 + g_last_signal);
    }
    return (1);
}

