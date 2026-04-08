#ifndef MINISHELL_H
# define MINISHELL_H

#include "./lexer/lexer.h"
# include "./env/env.h"
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
    int                 quoted;
    int                 heredoc_fd;
}   t_redirection;



typedef struct s_cmd
{
	
	char            **args; //argv
    t_redirection    *redirections; //linkedlist
}   t_cmd;

typedef enum e_node_type
{
	NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_GROUP
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
    t_ast       *active_ast;
    int         is_running;
    int         last_exit_status;
    char        *prompt_prefix;
} t_shell;


int	token_has_quotes(const char *s);
t_token* create_token(char *value , t_token_type type);
void append_token(t_token **head , t_token *new_token);
void	free_tokens(t_token *head);

#endif 