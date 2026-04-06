#ifndef PARSING_H
# define PARSING_H


# include "../lexer/lexer.h"
#include "../minishell.h"


#include <stdlib.h>


/* Forward declarations */
typedef struct s_ast t_ast;
typedef struct s_cmd t_cmd;
typedef struct s_redirection t_redirection;
typedef enum e_node_type t_node_type;



// syntax_check_lexer_1
int     is_command_token(t_token_type type);
int     is_redirection(t_token_type type);
int     is_command_delimiter(t_token_type type);
int     is_binary_operator(t_token_type type);
int set_unexpected(char **unexpected_token, int *unexpected_newline,char *token_value, int is_newline);
int is_same_redir_char_token(t_token *token, char c);
int redir_run_len(t_token *token, char c);

// syntax_check_lexer_2
int set_redir_unexpected(t_token *current,char **unexpected_token, int *unexpected_newline);
int syntax_check(t_token *head, char **unexpected_token, int *unexpected_newline);


t_ast *create_ast_node(t_node_type type);
t_ast *parse_pipeline(t_token **tokens);

int	count_words_in_cmd(t_token *token);
t_cmd *create_cmd(int argc);
void	init_cmd(t_cmd *cmd);
t_redirection *create_redirection(t_token *current);
void add_redirection(t_cmd *cmd, t_redirection *new_redir, t_redirection **last);
t_ast *init_command_node(t_token *tokens);
int handle_word_token(t_cmd *cmd, t_token *token, int *index);
int handle_redirection_token(t_cmd *cmd,t_token **tokens, t_redirection **last);
int fill_command_data(t_ast *node, t_token **tokens);
t_ast *build_command(t_token **tokens);

t_ast	*parse_next_expression(t_token **tokens, t_ast *left);


void free_redirections(t_redirection *r);
void free_command(t_cmd *cmd);
void free_ast(t_ast *ast);
int	process_command_tokens(t_ast *node, t_token **tokens, int *has_word);



t_ast	*create_binary_node(t_node_type type, t_ast *left, t_ast *right);
t_ast	*parse_primary_expression(t_token **tokens);
t_ast	*parse_pipe_expression(t_token **tokens);
t_ast	*parse_and_expression(t_token **tokens);

int	is_primary_start(t_token_type type);
int	check_redirection_syntax(t_token *current, char **unexpected_token,int *unexpected_newline);
int	check_command_syntax(t_token **tokens, char **unexpected_token,int *unexpected_newline);
int	check_primary_syntax(t_token **tokens, char **unexpected_token,int *unexpected_newline);
int	check_pipe_syntax(t_token **tokens, char **unexpected_token,int *unexpected_newline);
int	check_and_or_syntax(t_token **tokens, char **unexpected_token,int *unexpected_newline);


t_ast	*parse_group_expression(t_token **tokens);
int	is_primary_token(t_token *token);

t_ast	*parse_pipe_right(t_token **tokens, t_ast *left);

#endif
