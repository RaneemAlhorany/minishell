#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include "component/Libft/libft.h" 
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

t_env *build_env_list(char **envp);
t_env *env_new(char *key, char *value);
void env_add_back(t_env **head, t_env *new);
void free_env_list(t_env *head);
t_env *create_env_node(char *env_str);
t_env *find_env(t_env *env, char *key);
void    update_env(t_shell *shell, char *key, char *value);
char **env_list_to_envp(t_env *env);

#endif
