#include "shell.h"


char *prepare_input(char *line)
{
    char *input;

    if (!line || is_blank_line(line))
        return (NULL);
    input = ft_strdup(line);
    return (input);
}


t_token *get_tokens(char *input)
{
    t_token *tokens;

    tokens = lexer(input);
    return (tokens);
}

int expand_tokens_safe(t_token *tokens, t_shell *shell)
{
    if (!expand_tokens(tokens, shell))
        return (0);
    return (1);
}


void print_syntax_error(char *unexpected, int unexpected_newline)
{
    ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
    if (unexpected_newline)
        ft_putstr_fd("newline", 2);
    else if (unexpected)
        ft_putstr_fd(unexpected, 2);
    else
        ft_putstr_fd("newline", 2);
    ft_putendl_fd("'", 2);
}

static int	consume_heredocs_before_error(t_token *tokens, t_shell *shell)
{
    t_redirection	tmp_redir;
    int			fd;

    while (tokens)
    {
        if (tokens->type == TOKEN_HEREDOC
            && tokens->next && tokens->next->type == TOKEN_WORD)
        {
            tmp_redir.type = TOKEN_HEREDOC;
            tmp_redir.quoted = tokens->next->quoted;
            tmp_redir.heredoc_fd = -1;
            tmp_redir.filename = tokens->next->value;
            tmp_redir.next = NULL;
            fd = handle_heredoc(&tmp_redir, shell);
            if (fd < 0)
                return (0);
            close(fd);
            tokens = tokens->next;
        }
        tokens = tokens->next;
    }
    return (1);
}




int check_syntax(t_token *tokens, t_shell *shell)
{
    char *unexpected;
    int   unexpected_newline;
    t_token *saved_tokens;
    t_ast   *saved_ast;

    unexpected = NULL;
    unexpected_newline = 0;
    if (!syntax_check(tokens, &unexpected, &unexpected_newline))
    {
        saved_tokens = shell->active_tokens;
        saved_ast = shell->active_ast;
        shell->active_tokens = tokens;
        shell->active_ast = NULL;
        if (!consume_heredocs_before_error(tokens, shell))
        {
            shell->active_tokens = saved_tokens;
            shell->active_ast = saved_ast;
            return (0);
        }
        shell->active_tokens = saved_tokens;
        shell->active_ast = saved_ast;
        print_syntax_error(unexpected, unexpected_newline);
        return (0);
    }
    return (1);
}


