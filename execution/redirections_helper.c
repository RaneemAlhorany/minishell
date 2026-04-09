#include "execution.h"



int	is_whitespace_char(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}



int	is_ambiguous_redirect(t_redirection *r, char *filename)
{
    int	i;

    if (r->quoted)
        return (0);
    if (!filename || !*filename)
        return (1);
    i = 0;
    while (filename[i])
    {
        if (is_whitespace_char(filename[i]))
            return (1);
        i++;
    }
    return (0);
}


int	prepare_redirection_filename(t_redirection *r, t_shell *shell,char **resolved)
{
    char	*expanded;

    expanded = expand_string(r->filename, shell->env, shell->last_exit_status);
    if (!expanded)
        return (0);
    if (is_ambiguous_redirect(r, expanded))
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(r->filename, 2);
        ft_putendl_fd(": ambiguous redirect", 2);
        free(expanded);
        return (0);
    }
    *resolved = expanded;
    return (1);
}




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

    if (r->heredoc_fd >= 0)
    {
        fd = r->heredoc_fd;
        r->heredoc_fd = -1;
    }
    else
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
