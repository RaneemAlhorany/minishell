#ifndef BUILTIN_H
#define BUILTIN_H 

#include <unistd.h>
#include "../../minishell.h"
#include "../../env/env.h"

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;
typedef struct s_ast t_ast;



int  parse_n_flag(char **args, int *index);
void print_echo_args(char **args, int index);
int builtin_echo(t_cmd *cmd, t_shell *shell);

int builtin_pwd(t_cmd *cmd, t_shell *shell);

int builtin_env(t_cmd *cmd, t_shell *shell);

void remove_env(t_shell *shell, char *key);
int builtin_unset(t_cmd *cmd, t_shell *shell);

int	builtin_cd(t_cmd *cmd, t_shell *shell);
int	change_dir_and_update(t_shell *shell, char *path, char *pwd);
char *get_cd_path(t_cmd *cmd, t_shell *shell);



int builtin_exit(t_cmd *cmd, t_shell *shell);
int is_numeric(char *str);


int is_valid_identifier(char *key);
void print_export_list(t_env *env);
void update_or_add_env(t_shell *shell, char *key, char *value);
void handle_export_arg(char *arg, t_shell *shell);
int builtin_export(t_cmd *cmd, t_shell *shell);


#endif

