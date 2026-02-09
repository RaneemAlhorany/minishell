#include "minishell.h"





const char *token_type_to_string(t_token_type type)
{
    if (type == TOKEN_WORD)
        return "WORD";
    else if (type == TOKEN_PIPE)
        return "PIPE";
    else if (type == TOKEN_REDIR_IN)
        return "REDIR_IN";
    else if (type == TOKEN_REDIR_OUT)
        return "REDIR_OUT";
    else if (type == TOKEN_REDIR_APPEND)
        return "REDIR_APPEND";
    else if (type == TOKEN_HEREDOC)
        return "HEREDOC";
    else
        return "UNKNOWN";
}

void	print_tokens(t_token *tokens)//You don't need it, just let's see the results.
{
	t_token	*current;
	int		i;

	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	current = tokens;
	i = 0;
	printf("----------------------\n");
	printf(" TOKENS \n");
	while (current)
	{
		printf("[%d] Type: %s ||| Value: '%s'\n",i, token_type_to_string(current->type), current->value);
		current = current->next;
		i++;
	}
	printf("----------------------\n");
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}
