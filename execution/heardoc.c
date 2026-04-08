#include "execution.h"

static void	heredoc_child_sigint(int signum)
{
	(void)signum;
	g_last_signal = SIGINT;
}

static void	close_inherited_fds_except(int keep_fd)
{
    long	max_fd;
    int	fd;

    max_fd = sysconf(_SC_OPEN_MAX);
    if (max_fd < 0)
        max_fd = 1024;
    fd = 3;
    while (fd < (int)max_fd)
    {
        if (fd != keep_fd)
            close(fd);
        fd++;
    }
}

static void	cleanup_heredoc_child_state(t_shell *shell)
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
}

void	setup_heredoc_child_signals(void)
{
    t_sigaction	sa_int;
    t_sigaction	sa_quit;

    sa_int.sa_handler = heredoc_child_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

char	*read_heredoc_line(void)
{
    char	*buf;
    char	*tmp;
    char	c;
    ssize_t	n;
    size_t	len;
    size_t	cap;

    cap = 128;
    len = 0;
    buf = malloc(cap);
    if (!buf)
        return (NULL);
    while (1)
    {
        n = read(STDIN_FILENO, &c, 1);
        if (n == 0)
            break ;
        if (n < 0)
            return (free(buf), NULL);
        if (c == '\n')
            break ;
        if (len + 1 >= cap)
        {
            cap *= 2;
            tmp = malloc(cap);
            if (!tmp)
                return (free(buf), NULL);
            ft_memcpy(tmp, buf, len);
            free(buf);
            buf = tmp;
        }
        buf[len++] = c;
    }
    if (n == 0 && len == 0)
        return (free(buf), NULL);
    buf[len] = '\0';
    return (buf);
}


char	*strip_heredoc_quotes(const char *s)
{
    char	*result;
    int		i;
    int		j;

    if (!s)
        return (NULL);
    result = malloc(ft_strlen(s) + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (s[i] != '\'' && s[i] != '"')
            result[j++] = s[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}


int	is_limiter_match(const char *line, const char *limiter)
{
	if (!line || !limiter)
		return (0);
	return (ft_strlen(line) == ft_strlen(limiter)
		&& ft_strncmp(line, limiter, ft_strlen(line)) == 0);
}


void print_heredoc_warning(char *limiter)
{
    if (limiter)
    {
        ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
        ft_putstr_fd(limiter, 2);
        ft_putendl_fd("')", 2);
    }
    else
        ft_putendl_fd("minishell: warning: here-document at line 1 delimited by end-of-file", 2);
}

void process_heredoc_line(char *line, t_shell *shell, int write_fd, int quoted)
{
    char *expanded_line;

    if (quoted)
    {
		ft_putendl_fd(line, write_fd);
		return ;
	}
    expanded_line = expand_string(line, shell->env, shell->last_exit_status);
    if (expanded_line)
    {
        ft_putendl_fd(expanded_line, write_fd);
        free(expanded_line);
    }
    else
        ft_putendl_fd("", write_fd);
}

int	heredoc_loop(int write_fd, char *limiter, t_shell *shell, int quoted)
{
    char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = read_heredoc_line();
		if (!line)
		{
            if (get_last_signal() == SIGINT)
                return (1);
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            print_heredoc_warning(limiter);
            break ;
		}
		if (is_limiter_match(line, limiter))
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, shell, write_fd, quoted);
		free(line);
	}
    return (0);
}

int	wait_heredoc_child(pid_t pid, int *status)
{
    t_sigaction old_int;
    t_sigaction old_quit;
    t_sigaction ignore;

    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    sigaction(SIGINT, &ignore, &old_int);
    sigaction(SIGQUIT, &ignore, &old_quit);
    while (waitpid(pid, status, 0) < 0)
    {
        if (errno != EINTR)
        {
            sigaction(SIGINT, &old_int, NULL);
            sigaction(SIGQUIT, &old_quit, NULL);
            return (0);
        }
    }
    sigaction(SIGINT, &old_int, NULL);
    sigaction(SIGQUIT, &old_quit, NULL);
    return (1);
}

int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    int     tty_fd;
    char    *limiter;
    int     quoted;
    pid_t   pid;
    int     status;

    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (-1);
    }
    clear_last_signal();
    if (redirect)
    {
        quoted = redirect->quoted;
        limiter = strip_heredoc_quotes(redirect->filename);
    }
    else
    {
        quoted = 0;
        limiter = NULL;
    }
    if (!limiter)
    {
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

    pid = fork();
    if (pid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        free(limiter);
        return (-1);
    }
    if (pid == 0)
    {
        int interrupted;

        clear_last_signal();
        setup_heredoc_child_signals();
        tty_fd = -1;
        if (isatty(STDIN_FILENO))
            tty_fd = open("/dev/tty", O_RDONLY);
        if (tty_fd >= 0)
        {
            if (dup2(tty_fd, STDIN_FILENO) < 0)
            {
                close(tty_fd);
                close(fd[0]);
                close(fd[1]);
                free(limiter);
                cleanup_heredoc_child_state(shell);
                _exit(1);
            }
            close(tty_fd);
        }
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
    close(fd[1]);
    if (!wait_heredoc_child(pid, &status))
    {
        close(fd[0]);
        free(limiter);
        return (-1);
    }
    free(limiter);
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


static int	preload_heredocs_in_redirections(t_redirection *redir, t_shell *shell)
{
    int	fd;

    while (redir)
    {
        if (redir->type == TOKEN_HEREDOC)
        {
            if (redir->heredoc_fd >= 0)
            {
                close(redir->heredoc_fd);
                redir->heredoc_fd = -1;
            }
            fd = handle_heredoc(redir, shell);
            if (fd == -2)
                return (-2);
            if (fd < 0)
                return (-1);
            redir->heredoc_fd = fd;
        }
        redir = redir->next;
    }
    return (0);
}

int	preload_heredocs_ast(t_ast *node, t_shell *shell)
{
    int	status;

    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
        return (preload_heredocs_in_redirections(node->cmd->redirections, shell));
    if (node->type == NODE_PIPE || node->type == NODE_AND
        || node->type == NODE_OR || node->type == NODE_GROUP)
    {
        status = preload_heredocs_ast(node->pipe.left, shell);
        if (status != 0)
            return (status);
        if (node->type == NODE_GROUP)
            return (0);
        return (preload_heredocs_ast(node->pipe.right, shell));
    }
    return (0);
}




