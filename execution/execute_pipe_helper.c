
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
    setup_child_signals();//babo edit
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    exit(execute_ast(node->pipe.left, shell));
}



void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    setup_child_signals();//babo edit
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    exit(execute_ast(node->pipe.right, shell));
}
//لسا مش مرتاحلها بس هيك لازم تكون عشان ال signal handling في الpipe لما يكون في pipe لازم كل child process يتعامل مع ال signals بشكل منفصل عشان ما يأثروا على بعض وعلى الparent process
//لسا حاس ال while افضل 
int wait_for_pipe(pid_t left_pid, pid_t right_pid)
{//babo edit
    int status;
    int sig;

    waitpid(left_pid, NULL, 0);
    if (waitpid(right_pid, &status, 0) == -1)
        return (1);

    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (WIFSIGNALED(status))//babo edit
    {
        sig = WTERMSIG(status);
        if (sig == SIGQUIT)
            write(STDERR_FILENO, "Quit (core dumped)\n", 19);
        return (128 + sig);//babo edit
    }
    return (1);
}

