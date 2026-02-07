#include "./minishell.h"


#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)  // Ctrl+D
		{
			printf("exit\n");
			exit(0);
		}
		
		if (input[0])  // Only tokenize non-empty input
		{
			add_history(input);
			tokens = lexer(input);
			print_tokens(tokens);  // Debug: print tokens It's not required, just for clarification.
			free_tokens(tokens);
		}
		free(input);
	}
	return (0);
}


//t_token *head = NULL;
//append_token(&head, new_token);
