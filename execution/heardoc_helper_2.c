#include "execution.h"


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
