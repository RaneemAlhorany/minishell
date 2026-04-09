#include "execution.h"



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




int	handle_file_redirection(t_redirection *r, t_shell *shell,int flags, int std_fd)
{
	char	*filename;

	if (!prepare_redirection_filename(r, shell, &filename))
		return (0);
	if (!redirect_fd(filename, flags, std_fd))
	{
		free(filename);
		return (0);
	}
	free(filename);
	return (1);
}



int	process_redirection(t_redirection *r, t_shell *shell, int saved_stdin)
{
	if (r->type == TOKEN_REDIRECT_IN)
		return (handle_file_redirection(r, shell, O_RDONLY, STDIN_FILENO));
	else if (r->type == TOKEN_REDIRECT_OUT)
		return (handle_file_redirection(r, shell,
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
	else if (r->type == TOKEN_REDIRECT_APPEND)
		return (handle_file_redirection(r, shell,
				O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO));
	else if (r->type == TOKEN_HEREDOC)
		return (handle_heredoc_redirect(r, shell, saved_stdin));
	return (1);
}







// int process_redirection(t_redirection *r, t_shell *shell, int saved_stdin)
// {
//     char    *filename;

//     if (r->type == TOKEN_REDIRECT_IN)
//     {
//         if (!prepare_redirection_filename(r, shell, &filename))
//             return (0);
//         if (!redirect_fd(filename, O_RDONLY, STDIN_FILENO))
//         {
// 			free(filename);
// 			return (0);
// 		}
// 		free(filename);
// 		return (1);
//     }
//     else if (r->type == TOKEN_REDIRECT_OUT)
//     {
//         if (!prepare_redirection_filename(r, shell, &filename))
//             return (0);
//         if (!redirect_fd(filename, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO))
//         {
// 			free(filename);
// 			return (0);
// 		}
// 		free(filename);
// 		return (1);
//     }
//     else if (r->type == TOKEN_REDIRECT_APPEND)
//     {
//         if (!prepare_redirection_filename(r, shell, &filename))
//             return (0);
//         if (!redirect_fd(filename, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO))
//         {
// 			free(filename);
// 			return (0);
// 		}
// 		free(filename);
// 		return (1);
//     }
//     else if (r->type == TOKEN_HEREDOC)
//         return handle_heredoc_redirect(r, shell, saved_stdin);
//     return (1);
// }

