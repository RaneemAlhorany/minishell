#include "execution.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int execute_pipe_node(t_ast *node, t_shell *shell)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     status;

    if (!node || node->type != NODE_PIPE || !node->pipe.left || !node->pipe.right)
        return (execute_command_node(node, shell));

    if (pipe(pipe_fd) == -1)
        return (1);

    left_pid = fork();
    if (left_pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (1);
    }

    if (left_pid == 0)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        _exit(execute_ast(node->pipe.left, shell));
    }

    right_pid = fork();
    if (right_pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(left_pid, NULL, 0);
        return (1);
    }

    if (right_pid == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        _exit(execute_ast(node->pipe.right, shell));
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(left_pid, NULL, 0);
    if (waitpid(right_pid, &status, 0) == -1)
        return (1);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

int execute_ast(t_ast *node , t_shell *shell)
{
    if (!node)
        return (0);

    if (node->type == NODE_COMMAND)
        return (execute_command_node(node, shell));
    if (node->type == NODE_PIPE)
        return (execute_pipe_node(node, shell));
    return (0);
}











