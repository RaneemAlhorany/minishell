#include "tree.h"

int spawn_left_pipe(t_ast *node, char **envp, int fd[2], pid_t *left_pid)
{
    *left_pid = fork();
    if (*left_pid == -1)
        return (1);
    if (*left_pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        exit(execute_ast(node->left, envp));
    }
    return (0);
}

int spawn_right_pipe(t_ast *node, char **envp, int fd[2], pid_t *right_pid)
{
    *right_pid = fork();
    if (*right_pid == -1)
        return (1);
    if (*right_pid == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        exit(execute_ast(node->right, envp));
    }
    return (0);
}

int exec_pipe_node(t_ast *node, char **envp)
{
    int     fd[2];
    pid_t   left_pid;
    pid_t   right_pid;
    int     status;
    int     ret;

    ret = 0;
    if (pipe(fd) == -1)
        ret = 1;
    else if (spawn_left_pipe(node, envp, fd, &left_pid))
        ret = 1;
    else if (spawn_right_pipe(node, envp, fd, &right_pid))
        ret = 1;
    close(fd[0]);
    close(fd[1]);
    if (!ret)// مش متاكد اذا الاحس احطها لوب او هيك المشكله مافي شي اقرئ منه انو الحسن و اذا راح تعمل مشاكل او لا 
    {
        waitpid(left_pid, NULL, 0);
        waitpid(right_pid, &status, 0);
        if (WIFEXITED(status))
            ret = WEXITSTATUS(status);
        else
            ret = 1;
    }
    return (ret);
}

int execute_ast(t_ast *node, char **envp)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD)
        return (executor(node->cmd, envp));
    return (exec_pipe_node(node, envp));
}
