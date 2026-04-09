#ifndef BUILTIN_H
#define BUILTIN_H 

#include <unistd.h>
#include "../../minishell.h"
#include "../../env/env.h"
#include "../../Libft/libft.h"
#include <limits.h>

typedef struct s_shell t_shell;
typedef struct s_cmd t_cmd;
typedef struct s_ast t_ast;


//cd
void	print_cd_help_part_1();
void	print_cd_help_part_2();
char	*get_cd_path(t_cmd *cmd, t_shell *shell);
char *expand_path(char *path, t_shell *shell);
int change_dir_and_update(t_shell *shell, char *path, char *pwd);
int builtin_cd(t_cmd *cmd, t_shell *shell);
char    *get_parent_path(char *pwd);
char	*get_depending_path(t_shell *shell , char *goal);



//shared
void update_env_list(t_env **env, char *key, char *value);
int  parse_char_flag(char **args, int *index , char character);
void handle_existing(t_env *existing, char *value);
int	is_echo_n_option(const char *arg);


//echo
int	is_echo_option(const char *arg);
int	parse_echo_options(char **args, int *index);
void print_args(char **args, int index, t_shell *shell);
void clear_prompt_prefix(t_shell *shell);
char *append_expanded(char *result, char *arg, t_shell *shell);
char *append_space_if_needed(char *result, int has_next);
char *build_deferred_prompt_prefix(char **args, int index, t_shell *shell);
int	handle_no_args_echo(t_shell *shell);
int	handle_deferred_echo(char **args, int index, t_shell *shell);
void	print_echo_output(char **args, int index, t_shell *shell, int n_flag);
int	builtin_echo(t_cmd *cmd, t_shell *shell);


//env
void handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i);
int handle_env_command_error(t_cmd *cmd, int i);
void print_env(t_env *env);
int handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i);
int builtin_env(t_cmd *cmd, t_shell *shell);


//////// exit
int check_digits(char *str);
char *remove_quotes(char *str);
int handle_no_args(t_shell *shell);
int handle_numeric_error(char *arg, char *trimmed, t_shell *shell);
int handle_too_many_args(t_shell *shell, char *trimmed);
int is_numeric(char *str);
void print_exit_if_interactive(void);
int get_exit_status(char *trimmed, long long value, t_shell *shell);
int    check_overflow(unsigned long long res, int digit, int sign);
int    ft_isspace(char c);
int    parse_exit_argument(const char *str, long long *value);
int ft_atoll(const char *str, long long *value);
int skip_spaces_and_get_sign(const char *str, int *sign);
int parse_digits(const char *str, int *i, unsigned long long *res, int sign);
int set_result(unsigned long long res, int sign, long long *value);
int builtin_exit(t_cmd *cmd, t_shell *shell);



//export
//helper 1 :
void print_one_env(t_env *node);
void sort_env(t_env **arr, int count);
t_env **collect_exported(t_env *env, int count);
int count_exported(t_env *env);
void print_export_list(t_env *env);
//helper 2 :
int	handle_export_flow(t_cmd *cmd, t_shell *shell, int i, int flag_n);
int handle_export_n(t_cmd *cmd, t_shell *shell,int i);
int parse_export_arg(char *arg, char **key, char **value);
int	extract_key_value(char *arg, char **key, char **value);
int is_valid_identifier(char *key);
//helper 3
int	is_visible_export(t_env *env);
void	apply_export_n(t_shell *shell, char *key, char *value);
void	handle_export_n_logic(t_shell *shell, t_env *node, char *key, char *value);
void remove_export_flag(t_shell *shell, char *key);
int	parse_export_options(char **args, int *i, int *flag_p, int *flag_n);
//helper 4 :
int		handle_export_arg(char *arg, t_shell *shell);
int	extract_export_data(char *arg, t_shell *shell,char **key, char **value);
char *get_value(char *equal);
int validate_identifier_export(char *key, char *value, char *equal);
int	is_only_pn_options(const char *s, int *flag_p, int *flag_n);
//export
int builtin_export(t_cmd *cmd, t_shell *shell);


//pwd
int	parse_pwd_options(t_cmd *cmd, char *mode);
char	*get_pwd_value(char mode, t_shell *shell);
int builtin_pwd(t_cmd *cmd, t_shell *shell);

//unset
void remove_env(t_shell *shell, char *key);
char *strip_quotes(char *str);
int handle_unset_option(t_cmd *cmd, int *i);
void process_unset_args(t_cmd *cmd, t_shell *shell, int i);
int builtin_unset(t_cmd *cmd, t_shell *shell);



#endif
