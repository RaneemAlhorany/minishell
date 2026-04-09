#ifndef SHELL_H
#define SHELL_H

#include "../env/env.h"
#include "../lexer/lexer.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include "../Libft/libft.h"


// helper functions 1
int	is_str_numeric(const char *s);
void	free_shell(t_shell *shell);
char	*get_last_arg_from_cmd(t_cmd *cmd);
char	*get_last_arg_from_ast(t_ast *ast);
void free_2D(char **dirs);


// helper functions 2
int	expand_tokens(t_token *tokens, t_shell *shell);
int	is_blank_line(const char *s);
int handle_prepare_failure(t_shell *shell, t_token *tokens_head);
void set_active_state(t_shell *shell, t_token *tokens, t_ast *ast);
int execute_and_update(t_shell *shell, t_ast *ast);


// helper functions 3
char *prepare_input(char *line);
t_token *get_tokens(char *input);
int expand_tokens_safe(t_token *tokens, t_shell *shell);
void print_syntax_error(char *unexpected, int unexpected_newline);
int check_syntax(t_token *tokens);



// helper functions 4
t_ast *prepare_execution(t_shell *shell, char *line, t_token **tokens_head);
void cleanup_execution(t_shell *shell, t_ast *ast, t_token *tokens);
int execute_line(t_shell *shell, char *line);
void increment_shlvl(t_shell *shell);

 int	handle_prepare(t_shell *shell,t_token *tokens_head, t_ast *ast);


 int	handle_heredoc_shell(t_shell *shell,t_ast *ast, t_token *tokens_head);

 int	execute_phase(t_shell *shell, t_ast *ast);
//helper 5
void	shell_interactive(t_shell *shell);
char	*build_prompt(t_shell *shell);
void	handle_sigint(t_shell *shell);
void	process_line(t_shell *shell, char *line);


// shell 
t_shell * init_shell(char **envp);
int get_current_level(t_env *shlvl_node);
void print_shlvl_warning(int level);
int compute_next_level(int current_level);
void update_shlvl_value(t_shell *shell, int level);













#endif





