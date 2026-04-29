/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:24 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:58 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "../signals/signals.h"
# include "./builtins/builtin.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_wildcard_read_state
{
	char								buffer[512];
	char								line[1024];
	ssize_t								bytes;
	int									index;
	int									line_len;
}										t_wildcard_read_state;

typedef enum e_builtin_type
{
	BUILTIN_NONE,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}										t_builtin_type;

typedef struct stat						t_stat;

typedef struct s_wildcard_collect_ctx
{
	const char							*pattern;
	char								***matches;
	int									*count;
	int									*cap;
}										t_wildcard;

typedef struct s_wildcard_collect_ctx	t_wildcard;
typedef struct s_shell					t_shell;
typedef struct s_cmd					t_cmd;
typedef struct s_redirection			t_redirection;

// execute_ast.c
int										execute_ast(t_ast *node,
											t_shell *shell);

// execute_builtin.c
int										execute_builtin(t_cmd *cmd,
											t_shell *shell,
											t_builtin_type type);
t_builtin_type							get_builtin_type(char *cmd);

// execute_command_1.c
int										is_assignment_word(char *arg);
int										handle_assignment_only_command(t_ast *n,
											t_shell *shell);
int										handle_empty_command(t_ast *node,
											t_shell *shell);
int										execute_command_node(t_ast *node,
											t_shell *shell);

// execute_command_2.c
int										set_shell_assignment(t_shell *shell,
											char *arg);
char									*extract_key_or_value(char *arg, int i);
int										create_new_node(t_shell *shell,
											char *key, char *value);
int										handle_command_execution(t_ast *node,
											t_shell *shell);

// execute_external_1.c
int										prepare_execut(t_cmd *cmd,
											t_shell *shell, char **path,
											int *is_mini);
int										run_execution(t_cmd *cmd,
											t_shell *shell, char **envp,
											int saved[2]);
int										backup_std_fds(int *save_stdin,
											int *save_stdout, char **envp);
int										prepare_external(t_cmd *cmd,
											t_shell *shell, char **envp,
											int saved[2]);
int										execute_external(t_cmd *cmd,
											t_shell *shell);

// execute_external_2.c
int										resolve_and_validate(t_cmd *cmd,
											t_shell *shell, char **cmd_path);
char									*resolve_path_or_fail(t_cmd *cmd,
											t_shell *shell, int path_available);
char									*resolve_command_path(t_cmd *cmd,
											t_shell *shell);
char									**get_path_dirs(t_shell *shell);
char									*search_in_dirs(char **dirs,
											char *name);

// execute_external_3.c
char									*join_path(const char *dir,
											const char *cmd);
void									print_command_not_found(char *cmd);
char									*build_error_line(const char *prefix,
											const char *name,
											const char *suffix);
int										validate_command_access(char *cmd_path,
											t_cmd *cmd);
int										is_minishell_command(char *cmd);

// execute_external_4.c
int										execute_with_fork(t_cmd *cmd,
											t_shell *shell, char *cmd_path,
											char **envp);
void									try_sh_fallback(t_cmd *cmd,
											char *cmd_path, char **envp);
char									**build_sh_fallback_args(t_cmd *cmd,
											char *cmd_path);
void									handle_exec_error(t_cmd *cmd,
											char *cmd_path, char **envp,
											t_shell *shell);
int										finalize_and_wait(pid_t pid,
											int is_mini);

// execute_pipe_helper.c
int										wait_for_pipe(pid_t left_pid,
											pid_t right_pid);
int										wait_loop(pid_t left_pid,
											pid_t right_pid, int *right_status);

// execute_pipe.c
void									execute_right_child(t_ast *node,
											t_shell *shell, int pipe_fd[2]);
pid_t									fork_right_process(t_ast *node,
											t_shell *shell, int pipe_fd[2],
											pid_t left_pid);
void									execute_left_child(t_ast *node,
											t_shell *shell, int pipe_fd[2]);
pid_t									fork_left_process(t_ast *node,
											t_shell *shell, int pipe_fd[2]);
int										execute_pipe_node(t_ast *node,
											t_shell *shell);

// heredoc_helper_1.c
void									setup_child_stdin(int *tty_fd,
											int fd[2], char *limiter,
											t_shell *shell);
int										heredoc_loop(int write_fd,
											char *limiter, t_shell *shell,
											int quoted);
char									*read_heredoc_line(void);
char									*read_loop(char *buf, size_t *len,
											size_t *cap);
char									*resize_buffer(char *buf, size_t *cap,
											size_t len);

// heredoc_helper_2.c
int										handle_heredoc_eof(char *limiter);
void									process_heredoc_line(char *line,
											t_shell *shell, int write_fd,
											int quoted);
int										finalize_heredoc_parent(int fd[2],
											char *limiter, int pid);
int										wait_heredoc_child(pid_t pid,
											int *status);
int										handle_child_status(int fd[2],
											int status);

// heredoc.c
void									heredoc_child(int fd[2], char *limiter,
											t_shell *shell, int quoted);
int										fork_heredoc_child(int fd[2],
											char *limiter, t_shell *shell,
											int quoted);
char									*strip_heredoc_quotes(const char *s);
char									*prepare_limit(t_redirection *redirect,
											int *quoted);
int										handle_heredoc(t_redirection *redirect,
											t_shell *shell);

// redirections_helper.c
int										prepare_redirect_file(t_redirection *r,
											t_shell *shell, char **resolved);
int										is_ambiguous_redirect(t_redirection *r,
											char *filename);
int										redirect_fd(char *filename, int flags,
											int std_fd);
int										handle_heredoc_redct(t_redirection *r,
											t_shell *shell, int saved_stdin);
void									restore_sigpipe(t_sigaction *old_act);

// redirections.c
int										handle_file_redirect(t_redirection *r,
											t_shell *shell, int flags,
											int std_fd);
int										process_redirection(t_redirection *r,
											t_shell *shell, int saved_stdin);
int										apply_redirections(t_redirection *r,
											t_shell *shell);
int										handle_builtin_child(t_ast *n,
											t_shell *shell,
											t_builtin_type type);
int										execute_builtin_with_redirect(t_ast *n,
											t_shell *shell,
											t_builtin_type type);

// shared_method.c
void									restore_fds(int stdin_copy,
											int stdout_copy);
void									free_str_array(char **arr, int count);
void									free_parts(t_shell *shell);

// special_char.c
int										execute_child(t_ast *node,
											t_shell *shell);
int										execute_group_node(t_ast *node,
											t_shell *shell);
int										execute_logical_node(t_ast *node,
											t_shell *shell);

// wildcard_1.c
int										collect_matches(const char *pattern,
											char ***matches, int *count);
int										count_matches_in_cwd(char *pattern);
int										has_wildcard_chars(char *arg);
int										count_expanded_words(char **args);
int										expand_cmd_wildcards(t_cmd *cmd);

// wildcard_2.c
int										fill_matches_from_ls(t_wildcard *ctx);
void									exec_ls_child(int pipe_fd[2]);
int										read_ls_output(int fd, t_wildcard *ctx);
int										consume_chunk(t_wildcard *ctx,
											t_wildcard_read_state *state);
int										match_pattern(const char *pattern,
											const char *name);

// wildcard_3.c
int										wildcard_match(const char *pattern,
											const char *name);
void									handle_star(const char **pattern,
											const char **star,
											const char **match,
											const char **name);
int										skip_stars(const char *pattern);
int										append_match(char ***arr, int *count,
											int *cap, char *name);
int										resize_array(char ***arr, int *cap,
											int count);

// wildcard_4.c
int										flush_pending_line(t_wildcard *ctx,
											t_wildcard_read_state *state);
int										wait_and_check(pid_t pid, int status,
											int ok);
void									sort_match(char **matches, int count);
int										compare_match_names(char *a, char *b);
int										process_args(char **args,
											char **new_args);

// wildcard_5.c
int										copy_normal_arg(char **new_arg, int *j,
											char *arg);
int										handle_wildcard(char **new_arg, int *j,
											char *arg);
int										add_matches(char **new_args, int *j,
											char **matches, int match_count);

#endif