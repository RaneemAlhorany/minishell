/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:29 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:35:07 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include ".././Libft/libft.h"
# include ".././minishell.h"
# include "../shell/shell.h"
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;

// lexer
void						append_token(t_token **head, t_token *new_token);
t_token						*word_detection(char **input);
t_token						*operator_detection(char **input);
int							process_token(char **input, t_token **head);
t_token						*lexer(char *input);

// lexer_helper
int							move_through_word(char **input);
int							handle_quotes_for_lexer(char **input);
t_token						*handle_lexer_error(t_token *head, char *input);
char						check_unclosed_quotes(char *input);
int							skip_quote_content(char *input, int *i, char quote);

// lexer_utils
void						skip_spaces(char **input);
t_token						*match_and_or(char **input);
t_token						*match_double_redirect(char **input);
t_token						*detect_single_operator(char **input);
t_token						*helper_create_token(char **input, char *value,
								t_token_type type);

// token
t_token						*create_token(char *value, t_token_type type);
int							token_has_quotes(const char *s);
// void				free_tokens(t_token *head);

#endif