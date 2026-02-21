#ifndef MINISHELL_H
# define MINISHELL_H

# include "./env/env.h"
#include "./lexer/token_lexer.h"
#include "./expansion/expand.h"
#include "./parser/parsing.h"




typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}	t_node_type;

typedef struct s_redirection
{
    char    *filename;
    struct s_redirection *next;
    t_token_type         type;
}   t_redirection;



typedef struct s_cmd
{
	
	char            **args; //argv
    t_redirection    *redirections; //linkedlist
}   t_cmd;


typedef struct s_ast
{
    t_node_type type;
    union
    {
        t_cmd       *cmd;
        struct
        {
            struct s_ast *left;
            struct s_ast *right;
        } pipe;
    };
} t_ast;




















///////////////////////////////////
//! everything bellow need to edit 

#include "./A_edit_that_we_will_use_it_in_the_futeure/src/tree/tree.h"


t_cmd  *parser(t_token *tokens);
void   free_command_list(t_cmd *cmds);
void   free_tokens(t_token *tokens);
void   print_tokens(t_token *tokens);
int    executor(t_cmd *cmds, char **envp);
int	builtin_exit(t_cmd *cmd, char *input, t_token *tokens);
void	print_tokens(t_token *tokens);
const char *token_type_to_string(t_token_type type);


void	free_tokens(t_token *head);






#endif 








