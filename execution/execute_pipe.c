
#include "execution.h"



pid_t fork_left_process(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (-1);
    }
    if (pid == 0)
        execute_left_child(node, shell, pipe_fd);
    return (pid);
}

pid_t fork_right_process(t_ast *node, t_shell *shell, int pipe_fd[2], pid_t left_pid)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        waitpid(left_pid, NULL, 0);
        return (-1);
    }
    if (pid == 0)
        execute_right_child(node, shell, pipe_fd);
    return (pid);
}



int execute_pipe_node(t_ast *node, t_shell *shell)
{
    int     pipe_fd[2];
    pid_t   left_pid;
    pid_t   right_pid;

    if (!is_valid_pipe_node(node))
        return (execute_command_node(node, shell));

    if (create_pipe(pipe_fd))
        return (1);

    left_pid = fork_left_process(node, shell, pipe_fd);
    if (left_pid < 0)
        return (1);

    right_pid = fork_right_process(node, shell, pipe_fd, left_pid);
    if (right_pid < 0)
        return (1);

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    return (wait_for_pipe(left_pid, right_pid));
}
