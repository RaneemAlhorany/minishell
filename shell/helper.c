
#include "shell.h"



void free_2D(char **dirs)
{
    int i;

    if (!dirs)
        return;
    i = 0;
    while (dirs[i])
        free(dirs[i++]);
    free(dirs);
}



int	expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			expanded = expand_string(tokens->value, shell->env,
										shell->last_exit_status);
			if (!expanded)
				return (0);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
	return (1);
}



int	is_blank_line(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r')
			return (0);
		s++;
	}
	return (1);
}



t_ast	*prepare_execution(t_shell *shell,char *line, t_token **tokens_head)
{
	char	*input;
	t_token	*tokens;
	char	*unexpected;
	int		unexpected_newline;

	if (!shell || !line || is_blank_line(line))
		return (NULL);
	input = ft_strdup(line);
	if (!input)
		return (NULL);
	tokens = lexer(input);
	free(input);
	if (!tokens)
		return (NULL);
	*tokens_head = tokens;
	if (!expand_tokens(tokens, shell))
		return (NULL);
	unexpected = NULL;
	unexpected_newline = 0;
	if (!syntax_check(tokens, &unexpected, &unexpected_newline))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		if (unexpected_newline)
			ft_putstr_fd("newline", 2);
		else if (unexpected)
			ft_putstr_fd(unexpected, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putendl_fd("'", 2);
		return (NULL);
	}
	return (parse_pipeline(&tokens));
}


int	execute_line(t_shell *shell,char *line)
{
	t_token	*tokens_head;
	t_ast	*ast;
	int		status;

	tokens_head = NULL;
	ast = prepare_execution(shell, line, &tokens_head);
	shell->active_tokens = tokens_head;
	shell->active_ast = ast;
	if (!ast)
	{
		if (tokens_head)
			free_tokens(tokens_head);
		shell->active_tokens = NULL;
		shell->active_ast = NULL;
		return (2);
	}
	status = execute_ast(ast, shell);
	shell->last_exit_status = status;
	free_ast(ast);
	free_tokens(tokens_head);
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
	return (status);
}

