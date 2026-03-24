// edit this file after implement the heardoc redirection 

#include "execution.h"



int  apply_redirections(t_redirection *redirections, t_shell *shell)
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
                    return(fail_redirection (redirections->filename));
                dup2(opened_fd, STDIN_FILENO);
                close(opened_fd);

            }
            else if (redirections->type == TOKEN_REDIRECT_OUT)
            {
                opened_fd = open(redirections->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (opened_fd < 0)
                    return(fail_redirection (redirections->filename));
                dup2(opened_fd, STDOUT_FILENO);
                close(opened_fd);
            }
            else if (redirections->type == TOKEN_REDIRECT_APPEND)
            {
                opened_fd = open(redirections->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (opened_fd < 0)
                    return(fail_redirection (redirections->filename));
                dup2(opened_fd, STDOUT_FILENO);
                close(opened_fd);
            }
            else if (redirections->type == TOKEN_HEREDOC)
            {
                opened_fd = handle_heredoc(redirections, shell);
                if (opened_fd < 0)
                    return (0); 
                dup2(opened_fd, STDIN_FILENO);
                close(opened_fd);
            }

        redirections = redirections->next;
    }



    return(1);
}


int fail_redirection ( char *filename)
{
    perror(filename);
    return(0);
}
