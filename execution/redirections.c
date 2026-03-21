#include "execution.h"

int  apply_redirections(t_redirection *redirections)
{
    int opened_fd;

    if (!redirections)
        return ;

    while (redirections)
    {

            if (redirections->type == TOKEN_REDIRECT_IN)
            {
                opened_fd = open(redirections->filename, O_RDONLY);
                if (opened_fd < 0)
                    return(fail (redirections->filename));
                dup2(opened_fd, STDIN_FILENO);
                close(opened_fd);

            }
            else if (redirections->type == TOKEN_REDIRECT_OUT)
            {
                opened_fd = open(redirections->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (opened_fd < 0)
                    return(fail (redirections->filename));
                dup2(opened_fd, STDOUT_FILENO);
                close(opened_fd);
            }
            else if (redirections->type == TOKEN_REDIRECT_APPEND)
            {
                opened_fd = open(redirections->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (opened_fd < 0)
                    return(fail (redirections->filename));
                dup2(opened_fd, STDOUT_FILENO);
                close(opened_fd);
            }
            else if (redirections->type == TOKEN_HEREDOC)
            {
                // Handle heredoc redirection (not implemented here)
            }

        redirections = redirections->next;
    }
    return(1);
}


int fail ( char *filename)
{
    perror(filename);
    return(0);
}
