#include "execution.h"



 void	heredoc_child_sigint(int signum)
{
	(void)signum;
	g_last_signal = SIGINT;
}


 void	close_inherited_fds_except(int keep_fd)
{
    int	fd;

    fd = 3;
    while (fd < 1024)
    {
        if (fd != keep_fd)
            close(fd);
        fd++;
    }
}


 void	cleanup_heredoc_child_state(t_shell *shell)
{
    if (!shell)
        return ;
    if (shell->active_tokens)
    {
        free_tokens(shell->active_tokens);
        shell->active_tokens = NULL;
    }
    if (shell->active_ast)
    {
        free_ast(shell->active_ast);
        shell->active_ast = NULL;
    }
    free_shell(shell);
}


void	setup_heredoc_child_signals(void)
{
    t_sigaction	sa_int;
    t_sigaction	sa_quit;

    sa_int.sa_handler = heredoc_child_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}




char	*strip_heredoc_quotes(const char *s)
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
