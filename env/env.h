/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:17 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:14:21 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../Libft/libft.h"
# include "../shell/shell.h"
# include "../minishell.h"
# include <stdlib.h>

typedef struct s_env
{
	char				*key;
	char				*value;
	int					has_value;
	int					is_exported;
	struct s_env		*next;
}						t_env;

typedef struct s_shell	t_shell;

// get_env_value
char					*get_env_value(char *name, t_env *env);

// env_list
void					free_env_list(t_env *head);
int						init_env_value(t_env *node, char *value);
t_env					*env_new(char *key, char *value);
t_env					*create_env_node(char *env_str);
t_env					*build_env_list(char **envp);

// env
char					*build_env_line(t_env *env);
int						append_envp_entry(char **envp, int *i, t_env *env);
int						count_valid_env(t_env *env);
char					**env_list_to_envp(t_env *env);

// env_helper
void					env_add_back(t_env **head, t_env *new);
void					add_new_env(t_shell *shell, char *key, char *value);
t_env					*find_env(t_env *env, char *key);
void					update_env(t_shell *shell, char *key, char *value);

#endif
