
#include "execution.h"


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

    setup_child_signals();//babo edit
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    status = execute_ast(node->pipe.left, shell);
    if (shell->active_tokens)
    {
        free_tokens(shell->active_tokens);
        shell->active_tokens = NULL;
    }
    free_ast(node);
    free_shell(shell);
    rl_clear_history();
    _exit(status);
}



void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    int status;

    setup_child_signals();//babo edit
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    status = execute_ast(node->pipe.right, shell);
    if (shell->active_tokens)
    {
        free_tokens(shell->active_tokens);
        shell->active_tokens = NULL;
    }
    free_ast(node);
    free_shell(shell);
    rl_clear_history();
    _exit(status);
}

int wait_for_pipe(pid_t left_pid, pid_t right_pid)
{
    int status;
    int sig;

    waitpid(left_pid, NULL, 0);
    if (waitpid(right_pid, &status, 0) == -1)
        return (1);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))
    {
        sig = WTERMSIG(status);
        if (sig == SIGQUIT)
            write(STDERR_FILENO, "Quit (core dumped)\n", 19);
        return (128 + sig);
    }
    return (1);
}

