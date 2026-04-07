#ifndef EXECUTION_H
#define EXECUTION_H

#include "./builtins/builtin.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>
#include "signals/signals.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>




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
} t_builtin_type;

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;
typedef struct s_redirection t_redirection;


int execute_ast(t_ast *node , t_shell *shell);
int	execute_group_node(t_ast *node, t_shell *shell);
int	execute_child(t_ast *node, t_shell *shell);
void	cleanup_child(t_shell *shell, t_ast *node);
int	execute_logical_node(t_ast *node, t_shell *shell);


int execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type);
t_builtin_type get_builtin_type(char *cmd);

pid_t fork_left_process(t_ast *node, t_shell *shell, int pipe_fd[2]);
pid_t fork_right_process(t_ast *node, t_shell *shell, int pipe_fd[2], pid_t left_pid);
int execute_pipe_node(t_ast *node, t_shell *shell);

int is_valid_pipe_node(t_ast *node);
void execute_left_child(t_ast *node, t_shell *shell, int pipe_fd[2]);
void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2]);
int wait_for_pipe(pid_t left_pid, pid_t right_pid);

// helper execution functions 1
int	is_executable_non_directory(char *path);
char *find_program_on_path(char *name, t_shell *shell);
char **get_path_dirs(t_shell *shell);
char *search_in_dirs(char **dirs, char *name);
char *join_path(const char *dir, const char *cmd);

// helper execution functions 2
int is_valid_external_cmd(t_cmd *cmd, t_shell *shell);
int is_valid_command(t_ast *node);
int expand_cmd_wildcards(t_cmd *cmd);
void restore_fds(int stdin_copy, int stdout_copy);
char *resolve_command_path(t_cmd *cmd, t_shell *shell);
int handle_command_not_found(char *cmd_name, char *cmd_path, char **envp);

// helper execution functions 3
void	cleanup_child_state(t_shell *shell);
void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp , t_shell *shell);
int wait_for_child(pid_t pid);
char **prepare_envp(t_shell *shell);




int execute_builtin_with_redirection(t_ast *node, t_shell *shell, t_builtin_type type);
int handle_empty_command(t_ast *node, t_shell *shell);
int handle_command_execution(t_ast *node, t_shell *shell);
int execute_command_node(t_ast *node, t_shell *shell);

int	is_limiter_match(const char *line, const char *limiter);
void print_heredoc_warning(char *limiter);
void process_heredoc_line(char *line, t_shell *shell, int write_fd, int quoted);
void heredoc_loop(int write_fd, char *limiter, t_shell *shell, int quoted);
int handle_heredoc(t_redirection *redirect, t_shell *shell);

int  redirect_fd(char *filename, int flags, int std_fd);
int handle_heredoc_redirect(t_redirection *r, t_shell *shell, int saved_stdin);
int process_redirection(t_redirection *r, t_shell *shell, int saved_stdin);
int apply_redirections(t_redirection *redirections, t_shell *shell);
int fail_redirection ( char *filename);


int is_path_available(t_shell *shell);
char *resolve_path_or_fail(t_cmd *cmd, t_shell *shell,char **envp, int path_available);
int validate_command_access(char *cmd_path, t_cmd *cmd, char **envp);
int execute_with_fork(t_cmd *cmd, t_shell *shell,char *cmd_path, char **envp);
int execute_external(t_cmd *cmd, t_shell *shell);





#endif