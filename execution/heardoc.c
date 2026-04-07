#include "execution.h"


static char	*strip_heredoc_quotes(const char *s)
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

void heredoc_loop(int write_fd, char *limiter, t_shell *shell, int quoted)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            if (get_last_signal() != SIGINT)
                print_heredoc_warning(limiter);
            break;
        }
        if (is_limiter_match(line, limiter))
        {
            free(line);
            break;
        }
        process_heredoc_line(line, shell, write_fd, quoted);
        free(line);
    }
}


int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    char    *limiter;
    int     quoted;

    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (-1);
    }

    quoted = (redirect) ? redirect->quoted : 0;
    limiter = strip_heredoc_quotes((redirect) ? redirect->filename : NULL);
    if (!limiter)
    {
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

    heredoc_loop(fd[1], limiter, shell, quoted);

    close(fd[1]);
    free(limiter);
    if (get_last_signal() == SIGINT)
    {
		close(fd[0]);
		return (-2);
	}
    return (fd[0]);
}




