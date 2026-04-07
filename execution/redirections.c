#include "execution.h"

static int	is_whitespace_char(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static int	is_ambiguous_redirect(t_redirection *r, char *filename)
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

static int	prepare_redirection_filename(t_redirection *r, t_shell *shell,
    char **resolved)
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
    char    *filename;

    if (r->type == TOKEN_REDIRECT_IN)
    {
        if (!prepare_redirection_filename(r, shell, &filename))
            return (0);
        if (!redirect_fd(filename, O_RDONLY, STDIN_FILENO))
        {
			free(filename);
			return (0);
		}
		free(filename);
		return (1);
    }
    else if (r->type == TOKEN_REDIRECT_OUT)
    {
        if (!prepare_redirection_filename(r, shell, &filename))
            return (0);
        if (!redirect_fd(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO))
        {
			free(filename);
			return (0);
		}
		free(filename);
		return (1);
    }
    else if (r->type == TOKEN_REDIRECT_APPEND)
    {
        if (!prepare_redirection_filename(r, shell, &filename))
            return (0);
        if (!redirect_fd(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO))
        {
			free(filename);
			return (0);
		}
		free(filename);
		return (1);
    }
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
    ft_putstr_fd("minishell: ", 2);
    perror(filename);
    return(0);
}
