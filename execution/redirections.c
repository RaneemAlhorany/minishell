#include "execution.h"


int  redirect_fd(char *filename, int flags, int std_fd)
{
    int fd;

    fd = open(filename, flags, 0644);
    if (fd < 0)
        return (fail_redirection(filename));

    if (dup2(fd, std_fd) < 0)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}





int handle_heredoc_redirect(t_redirection *r, t_shell *shell, int saved_stdin)
{
    int fd;

    if (dup2(saved_stdin, STDIN_FILENO) < 0)
        return (0);

    fd = handle_heredoc(r, shell);
    if (fd < 0)
        return (0);

    if (dup2(fd, STDIN_FILENO) < 0)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}


int process_redirection(t_redirection *r, t_shell *shell, int saved_stdin)
{
    if (r->type == TOKEN_REDIRECT_IN)
        return redirect_fd(r->filename, O_RDONLY, STDIN_FILENO);
    else if (r->type == TOKEN_REDIRECT_OUT)
        return redirect_fd(r->filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
    else if (r->type == TOKEN_REDIRECT_APPEND)
        return redirect_fd(r->filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
    else if (r->type == TOKEN_HEREDOC)
        return handle_heredoc_redirect(r, shell, saved_stdin);
    return (1);
}

int apply_redirections(t_redirection *redirections, t_shell *shell)
{
    int saved_stdin;

    if (!redirections)
        return (1);

    saved_stdin = dup(STDIN_FILENO);
    if (saved_stdin < 0)
        return (0);

    while (redirections)
    {
        if (!process_redirection(redirections, shell, saved_stdin))
        {
            close(saved_stdin);
            return (0);
        }
        redirections = redirections->next;
    }

    close(saved_stdin);
    return (1);
}



int fail_redirection( char *filename)
{
    perror(filename);
    return(0);
}
