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


int  parse_char_flag(char **args, int *index , char character);
int builtin_echo(t_cmd *cmd, t_shell *shell);
void print_args(char **args, int index, t_shell *shell);


void handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i);
int handle_env_command_error(t_cmd *cmd, int i);
void print_env(t_env *env);
void update_env_list(t_env **env, char *key, char *value);
int handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i);
int builtin_env(t_cmd *cmd, t_shell *shell);
void handle_existing(t_env *existing, char *value);


char *remove_quotes(char *str);
int check_digits(char *str);
int is_numeric(char *str);
int builtin_exit(t_cmd *cmd, t_shell *shell);


//////////export
int	parse_export_options(char **args, int *i, int *flag_p, int *flag_n);
int	is_only_pn_options(const char *s, int *flag_p, int *flag_n);
int builtin_export(t_cmd *cmd, t_shell *shell);

////////// export helper1
void print_export_list(t_env *env);
int count_exported(t_env *env);
t_env **collect_exported(t_env *env, int count);
void sort_env(t_env **arr, int count);
void print_one_env(t_env *node);

///////// export helper2
int	handle_export_flow(t_cmd *cmd, t_shell *shell, int i, int flag_n);
int handle_export_n(t_cmd *cmd, t_shell *shell,int i);
int parse_export_arg(char *arg, char **key, char **value);
int is_valid_identifier(char *key);
int	extract_key_value(char *arg, char **key, char **value);

///////// export helper3
void	apply_export_n(t_shell *shell, char *key, char *value);
void	handle_export_n_logic(t_shell *shell, t_env *node, char *key, char *value);
void remove_export_flag(t_shell *shell, char *key);

///////// export helper4
char *get_value(char *equal, t_shell *shell);
int validate_identifier_export(char *key, char *value, char *equal);
void	handle_export_arg(char *arg, t_shell *shell);
int	extract_export_data(char *arg, t_shell *shell,char **key, char **value);


int	parse_pwd_options(t_cmd *cmd, char *mode);
char	*get_pwd_value(char mode, t_shell *shell);
int builtin_pwd(t_cmd *cmd, t_shell *shell);


void remove_env(t_shell *shell, char *key);
char *strip_quotes(char *str);
int handle_unset_option(t_cmd *cmd, int *i);
void process_unset_args(t_cmd *cmd, t_shell *shell, int i);
int builtin_unset(t_cmd *cmd, t_shell *shell);



#endif

