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




int check_syntax(t_token *tokens)
{
    char *unexpected;
    int   unexpected_newline;

    unexpected = NULL;
    unexpected_newline = 0;
    if (!syntax_check(tokens, &unexpected, &unexpected_newline))
    {
        print_syntax_error(unexpected, unexpected_newline);
        return (0);
    }
    return (1);
}


