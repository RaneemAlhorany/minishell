#include "minishell.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->env)
		free_env_list(shell->env);
	free(shell);
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
