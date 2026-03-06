#ifndef ENV_H
# define ENV_H


char    *get_env_value(char *name, t_env *env);


t_env *build_env_list(char **envp);
t_env *env_new(char *key, char *value);
void env_add_back(t_env **head, t_env *new);
void free_env_list(t_env *head);
t_env *create_env_node(char *env_str);
//# example :
/*
    // USER=dracula
    // HOME=/home/dracula
    // key : USER , value = dracula
    // key : HOME , value = /home/dracula

*/


#endif



