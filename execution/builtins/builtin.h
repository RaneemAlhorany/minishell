#ifndef BUILTIN_H
#define BUILTIN_H 

#include <unistd.h>
#include "../../minishell.h"
#include "../../env/env.h"

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;
typedef struct s_ast t_ast;



void	print_cd_help_part_1();
void	print_cd_help_part_2();
char	*get_home_path(t_shell *shell);
char	*get_oldpwd_path(t_shell *shell);
char	*get_cd_path(t_cmd *cmd, t_shell *shell);
char *expand_path(char *path, t_shell *shell);
int change_dir_and_update(t_shell *shell, char *path, char *pwd);
int builtin_cd(t_cmd *cmd, t_shell *shell);


int  parse_n_flag(char **args, int *index);
void print_echo_args(char **args, int index);
int builtin_echo(t_cmd *cmd, t_shell *shell);


void handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i);
int handle_env_command_error(t_cmd *cmd, int i);
void print_env(t_env *env);
void update_env_list(t_env **env, char *key, char *value);
int handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i);
int builtin_env(t_cmd *cmd, t_shell *shell);


char *remove_quotes(char *str);
int check_digits(char *str);
int is_numeric(char *str);
int builtin_exit(t_cmd *cmd, t_shell *shell);


int is_valid_identifier(char *key);
void print_export_list(t_env *env);
void remove_export_flag(t_shell *shell, char *key);
void update_or_add_env(t_shell *shell, char *key, char *value);
int validate_identifier_export(char *key, char *value, char *equal);
char *get_key(char *arg, char *equal);
char *get_value(char *arg, char *equal, t_shell *shell);
void handle_export_arg(char *arg, t_shell *shell);
int builtin_export(t_cmd *cmd, t_shell *shell);


int	parse_pwd_options(t_cmd *cmd, char *mode);
char	*get_pwd_value(char mode, t_shell *shell);
int builtin_pwd(t_cmd *cmd, t_shell *shell);


void remove_env(t_shell *shell, char *key);
char *strip_quotes(char *str);
int handle_unset_option(t_cmd *cmd, int *i);
void process_unset_args(t_cmd *cmd, t_shell *shell, int i);
int builtin_unset(t_cmd *cmd, t_shell *shell);



#endif

