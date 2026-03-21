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

t_builtin_type get_builtin_type(char *cmd);
int execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type);


char *join_path(const char *dir, const char *cmd);
void free_dirs(char **dirs);
char **get_path_dirs(t_shell *shell);
char *search_in_dirs(char **dirs, char *name);
char *find_program_on_path(char *name, t_shell *shell);
int is_valid_external_cmd(t_cmd *cmd, t_shell *shell);


int is_valid_command(t_ast *node);
void restore_fds(int stdin_copy, int stdout_copy);
int execute_builtin_with_redirection(t_ast *node, t_shell *shell, t_builtin_type type);
int execute_command_node(t_ast *node, t_shell *shell);


char *resolve_command_path(t_cmd *cmd, t_shell *shell);
int handle_command_not_found(char *cmd_path, char **envp);
void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp);
int wait_for_child(pid_t pid);
int execute_external(t_cmd *cmd, t_shell *shell);


int is_valid_pipe_node(t_ast *node);
void execute_left_child(t_ast *node, t_shell *shell, int pipe_fd[2]);
void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2]);
int wait_for_pipe(pid_t left_pid, pid_t right_pid);
int create_pipe(int pipe_fd[2]);
pid_t fork_left_process(t_ast *node, t_shell *shell, int pipe_fd[2]);
pid_t fork_right_process(t_ast *node, t_shell *shell, int pipe_fd[2], pid_t left_pid);
int execute_pipe_node(t_ast *node, t_shell *shell);


int fail_redirection ( char *filename);
int  apply_redirections(t_redirection *redirections);


int execute_ast(t_ast *node , t_shell *shell);

#endif