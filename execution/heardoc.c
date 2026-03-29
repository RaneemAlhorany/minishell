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
        ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
        ft_putstr_fd(limiter, 2);
        ft_putendl_fd("')", 2);
    }
    else
        ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
}

void process_heredoc_line(char *line, t_shell *shell, int write_fd)
{
    char *expanded_line;

    expanded_line = expand_string(line, shell->env, shell->last_exit_status);
    if (expanded_line)
    {
        ft_putendl_fd(expanded_line, write_fd);
        free(expanded_line);
    }
    else
        ft_putendl_fd("", write_fd);
}

void heredoc_loop(int write_fd, char *limiter, t_shell *shell)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            print_heredoc_warning(limiter);
            break;
        }
        if (is_limiter_match(line, limiter))
        {
            free(line);
            break;
        }
        process_heredoc_line(line, shell, write_fd);
        free(line);
    }
}


int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    char    *limiter;

    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (-1);
    }

    limiter = (redirect) ? redirect->filename : NULL;

    heredoc_loop(fd[1], limiter, shell);

    close(fd[1]);
    return (fd[0]);
}




