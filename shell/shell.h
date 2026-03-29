#ifndef SHELL_H
#define SHELL_H

#include "./env/env.h"
#include "./lexer/lexer.h"

t_shell * init_shell(char **envp);
void	free_shell(t_shell *shell);
void	shell_interactive(t_shell *shell);



void free_2D(char **dirs);
int	expand_tokens(t_token *tokens, t_shell *shell);
int	is_blank_line(const char *s);
t_ast	*prepare_execution(t_shell *shell,char *line, t_token **tokens_head);
int	execute_line(t_shell *shell,char *line);


#endif





