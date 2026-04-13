#include "execution.h"



 int handle_fork_error(int fd[2], char *limiter)
{
    close_pipe(fd);
    free(limiter);
    return (-1);
}

 void setup_child_stdin(int *tty_fd, int fd[2], char *limiter, t_shell *shell)
{
    *tty_fd = -1;
    if (isatty(STDIN_FILENO))
        *tty_fd = open("/dev/tty", O_RDONLY);
    if (*tty_fd >= 0)
    {
        if (dup2(*tty_fd, STDIN_FILENO) < 0)
        {
            close(*tty_fd);
            close_pipe(fd);
            free(limiter);
            cleanup_heredoc_child_state(shell);
            _exit(1);
        }
        close(*tty_fd);
    }
}

 void heredoc_child(int fd[2], char *limiter,t_shell *shell, int quoted)
{
    int interrupted;
    int tty_fd;

    clear_last_signal();
    setup_heredoc_child_signals();
    setup_child_stdin(&tty_fd, fd, limiter, shell);

    close(fd[0]);
    close_inherited_fds_except(fd[1]);

    interrupted = heredoc_loop(fd[1], limiter, shell, quoted);

    close(fd[1]);
    free(limiter);
    cleanup_heredoc_child_state(shell);

    if (interrupted)
        _exit(130);
    _exit(0);
}


 int handle_child_status(int fd[2], int status)
{
    if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        || (WIFEXITED(status) && WEXITSTATUS(status) == 130))
    {
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, "\n", 1);
        g_last_signal = SIGINT;
        close(fd[0]);
        return (-2);
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
    {
        close(fd[0]);
        return (-1);
    }
    return (fd[0]);
}

static int	fork_heredoc_child(int fd[2], char *limiter, t_shell *shell, int quoted)
{
    pid_t	pid;

    pid = fork();
    if (pid < 0)
        return (handle_fork_error(fd, limiter));
    if (pid == 0)
        heredoc_child(fd, limiter, shell, quoted);
    close(fd[1]);
    return (pid);
}

static int	finalize_heredoc_parent(int fd[2], char *limiter, int pid)
{
    int	status;

    if (!wait_heredoc_child(pid, &status))
    {
        close(fd[0]);
        free(limiter);
        return (-1);
    }
    free(limiter);
    return (handle_child_status(fd, status));
}

int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    char    *limiter;
    int     quoted;
    int     pid;

    if (!init_heredoc_pipe(fd))
    {
        return (-1);
    }
    clear_last_signal();
    limiter = prepare_limiter(redirect, &quoted);
    if (!limiter)
    {
        return (close_pipe(fd), -1);
	}
	pid = fork_heredoc_child(fd, limiter, shell, quoted);
	if (pid < 0)
    {
		return (pid);
	}
	return (finalize_heredoc_parent(fd, limiter, pid));
}
