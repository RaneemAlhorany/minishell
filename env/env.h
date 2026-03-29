#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include "./Libft/libft.h" 
#include "../minishell.h"

typedef struct s_env
{
    char            *key;
    char            *value;
    int             has_value;
    int             is_exported;
    struct s_env    *next;
}   t_env;

typedef struct s_shell t_shell;

char    *get_env_value(char *name, t_env *env);

int	init_env_value(t_env *node, char *value);
t_env	*env_new(char *key, char *value);
void env_add_back(t_env **head, t_env *new);
t_env *create_env_node(char *env_str);
t_env *build_env_list(char **envp);


t_env *find_env(t_env *env, char *key);
void update_existing_env(t_env *node, char *value);
void add_new_env(t_shell *shell, char *key, char *value);
void update_env(t_shell *shell, char *key, char *value);
void free_env_list(t_env *head);


int count_valid_env(t_env *env);
char *build_env_line(t_env *env);
void free_envp_partial(char **envp, int i);
char **env_list_to_envp(t_env *env);


#endif
