#include "execution.h"
//babo edit
int	is_limiter_match(const char *line, const char *limiter)
{
	if (!line || !limiter)
		return (0);
	return (ft_strlen(line) == ft_strlen(limiter)
		&& ft_strncmp(line, limiter, ft_strlen(line)) == 0);
}

//babo edit
int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    char    *line;
    char    *expanded_line;
    char    *limiter;

    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (-1);
    }
    limiter = NULL;
    if (redirect)
        limiter = redirect->filename;
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            if (limiter)
            {
                ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
                ft_putstr_fd(limiter, 2);
                ft_putendl_fd("')", 2);
            }
            else
                ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
            break;
        }
        if (is_limiter_match(line, limiter))
        {
            free(line);
            break;
        }
        expanded_line = expand_string(line, shell->env, shell->last_exit_status);
        if (expanded_line)
        {
            ft_putendl_fd(expanded_line, fd[1]);
            free(expanded_line);
        }
        else
            ft_putendl_fd("", fd[1]); 

        free(line); 
    }
    close(fd[1]);
    return (fd[0]);
}


