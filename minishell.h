#ifndef MINISHEEL_H
# define MINISHEEL_H


#include "./lexer/token_lexer.h"

typedef struct s_cmd
{
	char            *cmd;
	char            **args;
	char            *infile;
	char            *outfile;
	int             infile_fd;
	int             outfile_fd;
	int             is_builtin;
	int             append;
	int             is_heredoc;
	struct s_cmd    *next;
}   t_cmd;

t_cmd  *parser(t_token *tokens);
void   free_command_list(t_cmd *cmds);
void   free_tokens(t_token *tokens);
void   print_tokens(t_token *tokens);
int    executor(t_cmd *cmds, char **envp);
int	builtin_exit(t_cmd *cmd, char *input, t_token *tokens);
void	print_tokens(t_token *tokens);
const char *token_type_to_string(t_token_type type);

////////////////////////
void	free_tokens(t_token *head);
int syntax_check(t_token *head);
int is_redirection(t_token_type type);










#endif 