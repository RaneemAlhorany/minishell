#ifndef MINISHELL_H
# define MINISHELL_H

# include "./env/env.h"
#include "./lexer/lexer.h"
#include "./expansion/expand.h"
#include "./parser/parsing.h"
#include "./execution/execution.h"
#include "./signals/signals.h"
#include "./shell/shell.h"

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
    t_token     *active_tokens;
    int         is_running;
    int         last_exit_status;
} t_shell;


#endif 