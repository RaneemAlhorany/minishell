/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:09 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:13 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../Libft/libft.h"
# include "../../env/env.h"
# include "../../minishell.h"
# include <limits.h>
# include <unistd.h>

typedef struct s_shell	t_shell;
typedef struct s_cmd	t_cmd;
typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

// cd
char					*get_depending_path(t_shell *shell, char *goal);
char					*get_cd_path(t_cmd *cmd, t_shell *shell);
char					*get_pwd_safe(t_shell *shell);
int						builtin_cd(t_cmd *cmd, t_shell *shell);
void					print_cd_help_part_1(void);

// cd helper
void					print_cd_help_part_2(void);
void					print_cd_help_part_3(void);
int						change_dir_and_update(t_shell *shell, char *path,
							char *pwd);
char					*resolve_new_pwd(char *path, char *pwd);
char					*get_parent_path(char *pwd);

// echo
int						handle_deferred_echo(char **args, int index,
							t_shell *shell);
int						is_echo_option(const char *arg);
int						parse_echo_options(char **args, int *index);
void					clear_prompt_prefix(t_shell *shell);
int						builtin_echo(t_cmd *cmd, t_shell *shell);

// echo helper
char					*build_deferred_prompt_prefix(char **args, int index);
char					*append_space_if_needed(char *result, int has_next);
void					print_echo_output(char **args, int index,
							t_shell *shell, int n_flag);

// env
int						handle_u_option(t_cmd *cmd, t_env **new_env, int *i);
int						process_option(t_cmd *cmd, t_env **new_env, int *i);
t_env					*copy_env_list(t_env *env);
int						handle_option(t_cmd *cmd, t_shell *shell,
							t_env **new_env, int *i);
int						builtin_env(t_cmd *cmd, t_shell *shell);

// env helper
void					remove_env_entry(t_env **env, char *key);
int						print_env_invalid_option(const char *arg);
void					handle_env_assignments(t_cmd *cmd, t_env **new_env,
							int *i);
int						execute_env_command(t_cmd *cmd, t_shell *shell,
							t_env **new_env, int i);
void					print_env(t_env *env);

// exit
int						parse_digits(const char *str, int *i,
							unsigned long long *res, int sign);
int						skip_spaces_and_get_sign(const char *str, int *sign);
int						ft_atoll(const char *str, long long *value);
int						check_digits(char *str);
int						builtin_exit(t_cmd *cmd, t_shell *shell);

// exit helper
int						handle_numeric_error(char *arg, char *trimmed,
							t_shell *shell);
int						handle_too_many_args(t_shell *shell, char *trimmed);

// export
int						builtin_export(t_cmd *cmd, t_shell *shell);

// export print
void					print_export_list(t_env *env);
t_env					**collect_exported(t_env *env, int count);
void					sort_env(t_env **arr, int count);
void					print_one_env(t_env *node);

// export options
int						parse_export_options(char **args, int *i, int *flag_p,
							int *flag_n);
int						is_only_pn_options(const char *s, int *flag_p,
							int *flag_n);
int						error_export_arg(t_cmd *cmd, int i);
int						handle_export_flow(t_cmd *cmd, t_shell *shell, int i,
							int flag_n);
int						handle_export_n(t_cmd *cmd, t_shell *shell, int i);

// export helper 1
int						parse_export_arg(char *arg, char **key, char **value);
int						assign_export_pair(char **key, char **value, char *arg);
int						is_valid_identifier(char *key);
void					handle_export_n_logic(t_shell *shell, t_env *n,
							char *key, char *value);
void					remove_export_flag(t_shell *shell, char *key);

// export helper 2
int						handle_export_arg(char *arg, t_shell *shell);
int						extract_export_data(char *arg, char **key,
							char **value);
int						assign_export_key(char *arg, char *equal, char **key);
int						assign_export_value(char *equal, char **key,
							char **value);
int						validate_identifier_export(char *key, char *value,
							char *equal);

// pwd
char					*get_pwd_value(char mode, t_shell *shell);
int						parse_pwd_option_arg(char *arg, char *mode);
int						parse_pwd_options(t_cmd *cmd, char *mode);
int						builtin_pwd(t_cmd *cmd, t_shell *shell);

// unset
int						consume_char_flag(char *arg, int *flag, char character);
int						is_matching_flag_arg(char *arg, char character);
int						parse_char_flag(char **args, int *index,
							char character);
int						handle_unset_option(t_cmd *cmd, int *i);
int						builtin_unset(t_cmd *cmd, t_shell *shell);

// unset helper
void					process_unset_args(t_cmd *cmd, t_shell *shell, int i);
void					remove_env(t_shell *shell, char *key);

// shared_method
void					update_env_list(t_env **env, char *key, char *value);
void					handle_existing(t_env *existing, char *value);

#endif
