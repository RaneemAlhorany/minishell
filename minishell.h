#ifndef MINISHELL_H
# define MINISHELL_H

# include "./env/env.h"
#include "./lexer/lexer.h"
#include "./expansion/expand.h"
#include "./parser/parsing.h"
#include "./execution/execution.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "signals/signals.h"



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

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE
}	t_node_type;

typedef struct s_ast
{
    t_node_type type;
    union
    {
        t_cmd       *cmd;//*
        struct
        {
            struct s_ast *left;
            struct s_ast *right;
        } pipe;
    };
} t_ast;


typedef struct s_shell
{
    t_env       *env; 
    int         is_running;
    int         last_exit_status;
} t_shell;

///////////////////////////////////
//! everything bellow need to edit 

// #include "./A_edit_that_we_will_use_it_in_the_futeure/src/tree/tree.h"


t_shell * init_shell(char **envp);
void free_2D(char **dirs);



int    executor(t_cmd *cmds, char **envp);
t_shell * init_shell(char **envp);







//////////////////////////////////////////

int	is_blank_line(const char *s);
t_ast	*prepare_execution(t_shell *shell,char *line, t_token **tokens_head);
int	execute_line(t_shell *shell,char *line);
void	shell_interactive(t_shell *shell);

void	free_shell(t_shell *shell);
int	expand_tokens(t_token *tokens, t_shell *shell);






#endif 