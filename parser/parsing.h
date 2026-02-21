#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"



int     syntax_check(t_token *head);
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


void free_redirections(t_redirection *r);
void free_command(t_cmd *cmd);
void free_ast(t_ast *ast);



#endif



