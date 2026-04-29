/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:11 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:55:13 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lexer/lexer.h"
# include "../minishell.h"
# include <stdlib.h>

typedef struct s_ast			t_ast;
typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;
typedef enum e_node_type		t_node_type;
typedef enum e_token_type		t_token_type;
typedef enum e_reserved_word
{
	RW_NONE,
	RW_IN,
	RW_DO,
	RW_DONE,
	RW_IF,
	RW_THEN,
	RW_ELIF,
	RW_ELSE,
	RW_FI,
	RW_WHILE,
	RW_UNTIL,
	RW_FOR,
	RW_CASE,
	RW_ESAC,
	RW_SELECT,
	RW_FUNCTION,
	RW_LBRACE,
	RW_RBRACE,
	RW_LBRACK2,
	RW_RBRACK2,
	RW_BANG
}								t_reserved_word;
typedef struct s_token			t_token;

//build_command_1.c
t_ast							*build_command(t_token **tokens);
t_ast							*init_command_node(t_token *tokens);
int								count_words_in_cmd(t_token *token);
int								count_unquoted_words(char *s);
t_cmd							*create_cmd(int argc);

//build_command_2.c
int								process_command_tokens(t_ast *node,
									t_token **tokens, int *has_word);
int								handle_word_token(t_cmd *cmd, t_token *token,
									int *index);
t_reserved_word					get_reserved_word_1(const char *word);
t_reserved_word					get_reserved_word_2(const char *word);
int								ensure_cmd_args_capacity(t_cmd *cmd,
									int needed_index);

//build_command_3.c
void							enter_data(t_cmd *cmd, char ***new_args,
									int *new_cap);
int								append_unquoted_words(t_cmd *cmd,
									t_token *token, int *index);
char							*next_unquoted_word(char **start);
int								handle_redirection_token(t_cmd *cmd,
									t_token **tokens, t_redirection **last);
t_redirection					*create_redirection(t_token *current);

//parser_helper.c
t_ast							*parse_pipe_right(t_token **tokens,
									t_ast *left);
t_ast							*create_binary_node(t_node_type type,
									t_ast *left, t_ast *right);
t_ast							*parse_next_expression(t_token **tokens,
									t_ast *left);

//parser.c
t_ast							*create_ast_node(t_node_type type);
t_ast							*parse_group_expression(t_token **tokens);
t_ast							*parse_pipe_expression(t_token **tokens);
t_ast							*parse_and_expression(t_token **tokens);
t_ast							*parse_pipeline(t_token **tokens);

//shared_method.c
int								is_redirection(t_token_type type);
int								is_command_delimiter(t_token_type type);

//syntax_check_lexer_1.c
int								set_unexpected(char **unexpected_token,
									int *unexpected_newline, char *token_value,
									int is_newline);
int								check_primary_syntax(t_token **tokens,
									char **unexpect_token, int *unexpect_line);
int								check_pipe_syntax(t_token **tokens,
									char **unexpected_token,
									int *unexpected_newline);
int								check_and_or_syntax(t_token **tokens,
									char **unexpected_token,
									int *unexpected_newline);
int								syntax_check(t_token *head,
									char **unexpected_token,
									int *unexpected_newline);

//syntax_check_lexer_2.c
int								check_command_syntax(t_token **tokens,
									char **unexpected_token,
									int *unexpected_newline);
int								check_redirection_syntax(t_token *current,
									char **unexpected_token,
									int *unexpected_newline);
int								set_redir_unexpected(t_token *current,
									char **unexpected_token,
									int *unexpected_newline);
int								redir_run_len(t_token *token, char c);
int								is_same_redir_char_token(t_token *token,
									char c);

#endif
