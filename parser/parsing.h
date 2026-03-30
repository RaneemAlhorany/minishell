#ifndef PARSING_H
# define PARSING_H


# include "../lexer/lexer.h"
#include "../minishell.h"

/* Forward declarations */
typedef struct s_ast t_ast;
typedef struct s_cmd t_cmd;
typedef struct s_redirection t_redirection;
typedef enum e_node_type t_node_type;





int     syntax_check(t_token *head, char **unexpected_token, int *unexpected_newline);
int     is_command_token(t_token_type type);
int     is_redirection(t_token_type type);

t_ast *create_ast_node(t_node_type type);
t_ast *parse_pipeline(t_token **tokens);
int is_pipe(t_token **tokens);
t_ast *create_pipe_node(t_token **tokens, t_ast *left);

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
int process_single_token(t_ast *node, t_token **tokens);
//int process_redirection(t_ast *node, t_token **tokens);
int process_word(t_ast *node, t_token **tokens);



void free_redirections(t_redirection *r);
void free_command(t_cmd *cmd);
void free_ast(t_ast *ast);
int	process_command_tokens(t_ast *node, t_token **tokens, int *has_word);


#endif
