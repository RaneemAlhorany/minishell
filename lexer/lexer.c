#include "minishell.h"



 void	print_unclosed_quote_error(char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putendl_fd("'", 2);
}


 t_token	*handle_lexer_error(t_token *head, char *input)
{
	char	unclosed_quote;

	unclosed_quote = check_unclosed_quotes(input);
	if (unclosed_quote)
		print_unclosed_quote_error(unclosed_quote);
	free_tokens(head);
	return (NULL);
}


 int	process_token(char **input, t_token **head)
{
	t_token	*new;

	new = operator_detection(input);
	if (!new)
		new = word_detection(input);
	if (!new)
		return (0);
	append_token(head, new);
	return (1);
}


 t_token	*lexer_loop(char *input, char *original_input)
{
	t_token	*head;

	head = NULL;
	while (*input)
	{
		skip_spaces(&input);
		if (!*input || *input == '#')
			break;
		if (!process_token(&input, &head))
			return (handle_lexer_error(head, original_input));
	}
	return (head);
}

t_token	*lexer(char *input)
{
	return (lexer_loop(input, input));
}




// t_token *lexer(char *input)
// {
//     t_token *head;
//     t_token *new;
//     char	unclosed_quote;
//     char	*original_input;

//     head = NULL;
//     original_input = input;
//     while (*input)
//     {
//         skip_spaces(&input);
//         if (!*input)
//             break;
//         if (*input == '#')
//             break;
//         new = operator_detection(&input);
//         if (new)
//             append_token(&head ,new);
//         else 
//         {
//             new = word_detection(&input);
//             if (new)
//                 append_token(&head ,new );
//             else 
//             {
//                 unclosed_quote = check_unclosed_quotes(original_input);
//                 if (unclosed_quote)
//                 {
//                     ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
//                     ft_putchar_fd(unclosed_quote, 2);
//                     ft_putendl_fd("'", 2);
//                 }
//                 free_tokens(head);
//                 return (NULL);
//             }
//         }
//     }
//     return (head);
// }




