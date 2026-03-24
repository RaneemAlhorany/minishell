
#include "execution.h"


int handle_heredoc(t_redirection *redirect, t_shell *shell)
{
    int     fd[2];
    char    *line;
    char *expanded_line;

    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(redirect->filename, 2);
            ft_putendl_fd("')", 2);
            break;
        }
        if (ft_strlen(line) == ft_strlen(redirect->filename) 
            && ft_strncmp(line, redirect->filename, ft_strlen(line)) == 0)
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


