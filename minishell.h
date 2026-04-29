/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:48 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 17:03:01 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./env/env.h"
# include "./expansion/expand.h"
# include "./lexer/lexer.h"
# include "./parser/parsing.h"
# include "./shell/shell.h"
# include "./signals/signals.h"
# include "signals/signals.h"
# include "./execution/execution.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_ast			t_ast;
typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC
}							t_token_type;

typedef struct s_redirection
{
	char					*filename;
	struct s_redirection	*next;
	t_token_type			type;
	int						quoted;
	int						heredoc_fd;
}							t_redirection;

typedef struct s_cmd
{
	char					**args;
	int						arg_cap;
	t_redirection			*redirections;
}							t_cmd;

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
	t_node_type				type;
	union
	{
		t_cmd				*cmd;
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		} s_pipe;
	};
}							t_ast;

typedef struct s_shell
{
	t_env					*env;
	t_token					*active_tokens;
	t_ast					*active_ast;
	int						in_child_process;
	int						is_running;
	int						last_exit_status;
	char					*prompt_prefix;
}							t_shell;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						quoted;
	struct s_token			*next;
}							t_token;

#endif