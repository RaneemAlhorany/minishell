/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:15 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:22:26 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../Libft/libft.h"
# include "../env/env.h"
# include "../minishell.h"
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_env			t_env;
typedef struct s_token			t_token;
typedef struct s_ast			t_ast;
typedef struct s_cmd			t_cmd;
typedef struct s_redirection	t_redirection;
typedef struct s_shell			t_shell;

//shell_execution.c
t_ast							*prepare_execution(t_shell *shell, char *line,
									t_token **tokens_head);
int								is_blank_line(const char *s);
int								check_syntax(t_token *tokens, t_shell *shell);
int								process_heredocs_on_error(t_token *tokens,
									t_shell *shell);
int								expand_tokens(t_token *tokens, t_shell *shell);

//shell_free_1.c
int								handle_prepare_failure(t_shell *shell,
									t_token *tokens_head);
void							free_tokens(t_token *head);
void							cleanup_execution(t_shell *shell, t_ast *ast,
									t_token *tokens);
void							free_ast(t_ast *ast);

//shell_free_2.c
void							free_command(t_cmd *cmd);
void							free_redirections(t_redirection *r);
void							free_shell(t_shell *shell);
void							free_2d(char **dirs);

//shell_helper_1.c
t_ast							*parse_pipeline(t_token **tokens);
int								handle_heredoc_shell(t_shell *shell, t_ast *ast,
									t_token *tokens_head);
int								preload_heredocs_ast(t_ast *node,
									t_shell *shell);
int								preload_heredocs_redirect(t_redirection *redir,
									t_shell *shell);
int								execute_and_update(t_shell *shell, t_ast *ast);

//shell_helper_2.c
char							*get_last_arg_from_ast(t_ast *ast);
char							*get_last_arg_from_cmd(t_cmd *cmd);

//shell.c
int								execute_line(t_shell *shell, char *line);
int								is_blank_input(char *line);
void							process_line(t_shell *shell, char *line);
char							*build_prompt(t_shell *shell);
void							shell_interactive(t_shell *shell);

//shlvl.c
int								compute_next_level(int current_level);
int								is_str_numeric(const char *s);
void							increment_shlvl(t_shell *shell);
t_shell							*init_shell(char **envp);

#endif
