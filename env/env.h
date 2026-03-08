#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include "black_box_project/Libft/libft.h" 
#include "../minishell.h"

//?????? 
typedef struct s_env
{
    char            *key;
    char            *value;
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
void	update_env(t_shell *shell, char *key, char *value);

//# example :
/*
    // USER=dracula
    // HOME=/home/dracula
    // key : USER , value = dracula
    // key : HOME , value = /home/dracula

*/


#endif



