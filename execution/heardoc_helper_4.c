
#include "execution.h"


int	preload_heredocs_ast(t_ast *node, t_shell *shell)
{
    int	status;

    if (!node)
        return (0);
    if (node->type == NODE_COMMAND)
        return (preload_heredocs_in_redirections(node->cmd->redirections, shell));
    if (node->type == NODE_PIPE || node->type == NODE_AND
        || node->type == NODE_OR || node->type == NODE_GROUP)
    {
        status = preload_heredocs_ast(node->pipe.left, shell);
        if (status != 0)
            return (status);
        if (node->type == NODE_GROUP)
            return (0);
        return (preload_heredocs_ast(node->pipe.right, shell));
    }
    return (0);
}


 int	preload_heredocs_in_redirections(t_redirection *redir, t_shell *shell)
{
    int	fd;

    while (redir)
    {
        if (redir->type == TOKEN_HEREDOC)
        {
            if (redir->heredoc_fd >= 0)
            {
                close(redir->heredoc_fd);
                redir->heredoc_fd = -1;
            }
            fd = handle_heredoc(redir, shell);
            if (fd == -2)
                return (-2);
            if (fd < 0)
                return (-1);
            redir->heredoc_fd = fd;
        }
        redir = redir->next;
    }
    return (0);
}


 int init_heredoc_pipe(int fd[2])
{
    if (pipe(fd) < 0)
    {
        perror("minishell: pipe");
        return (0);
    }
    return (1);
}


 char *prepare_limiter(t_redirection *redirect, int *quoted)
{
    char *limiter;

    if (redirect)
    {
        *quoted = redirect->quoted;
        limiter = strip_heredoc_quotes(redirect->filename);
    }
    else
    {
        *quoted = 0;
        limiter = NULL;
    }
    return (limiter);
}

 void close_pipe(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}
