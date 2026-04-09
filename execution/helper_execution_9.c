#include "execution.h"


 void	exec_ls_child(int pipe_fd[2])
{
    char	*argv[3];

    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    argv[0] = "/bin/ls";
    argv[1] = "-a1";
    argv[2] = NULL;
    execve("/bin/ls", argv, NULL);
    exit(1);
}

 int	read_from_pipe(int pipe_fd[2], t_wildcard_collect_ctx *ctx)
{
    int	ok;

    close(pipe_fd[1]);
    ok = read_ls_output(pipe_fd[0], ctx);
    close(pipe_fd[0]);
    return (ok);
}

 int	wait_and_check(pid_t pid, int status, int ok)
{
    if (waitpid(pid, &status, 0) < 0)
        return (0);
    if (!ok)
        return (0);
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        return (0);
    return (1);
}

 int	fill_matches_from_ls(t_wildcard_collect_ctx *ctx)
{
    int		pipe_fd[2];
    pid_t	pid;
    int		status;
    int		ok;

    if (!create_process(pipe_fd, &pid))
        return (0);
    if (pid == 0)
        exec_ls_child(pipe_fd);
    status = 0;
    ok = read_from_pipe(pipe_fd, ctx);
    return (wait_and_check(pid, status, ok));
}

int	collect_matches(const char *pattern, char ***matches, int *count)
{
    t_wildcard_collect_ctx	ctx;
    int				cap;

    ctx.pattern = pattern;
    ctx.matches = matches;
    ctx.count = count;
    ctx.cap = &cap;
    *matches = NULL;
    *count = 0;
    cap = 0;
    if (!fill_matches_from_ls(&ctx))
        return (0);
    if (*count > 1)
        sort_matches(*matches, *count);
    return (1);
}



