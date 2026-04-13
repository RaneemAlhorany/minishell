
#include "shell.h"

static int	should_expand_token(t_token *tokens, t_token *prev)
{
	if (tokens->type != TOKEN_WORD)
		return (0);
	if (!prev)
		return (1);
	if (prev->type == TOKEN_REDIRECT_IN || prev->type == TOKEN_REDIRECT_OUT)
		return (0);
	if (prev->type == TOKEN_REDIRECT_APPEND || prev->type == TOKEN_HEREDOC)
		return (0);
	return (1);
}



int	expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*expanded;
	t_token	*prev;

	prev = NULL;

	while (tokens)
	{
		if (should_expand_token(tokens, prev))
		{
			expanded = expand_string(tokens->value, shell->env,
										shell->last_exit_status);
			if (!expanded)
				return (0);
			free(tokens->value);
			tokens->value = expanded;
		}
		prev = tokens;
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


int handle_prepare_failure(t_shell *shell, t_token *tokens_head)
{
    if (tokens_head)
        free_tokens(tokens_head);
    shell->active_tokens = NULL;
    shell->active_ast = NULL;
    return (2);
}


void set_active_state(t_shell *shell, t_token *tokens, t_ast *ast)
{
    shell->active_tokens = tokens;
    shell->active_ast = ast;
}


int execute_and_update(t_shell *shell, t_ast *ast)
{
	char	*last_arg;
	int		status;

	last_arg = get_last_arg_from_ast(ast);
	if (last_arg)
		update_env(shell, "_", last_arg);
    status = execute_ast(ast, shell);
    return (status);
}

