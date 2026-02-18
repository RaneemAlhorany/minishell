#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

char    *get_env_value(char *name, t_env *env);


//# example :
/*
    // USER=dracula
    // HOME=/home/dracula
    // key : USER , value = dracula
    // key : HOME , value = /home/dracula

*/


#endif



// void    expand_tokens(t_token *list, t_env *env, int last_status)
// {
//     while (list)
//     {
//         list->value = expand_string(list->value, env, last_status);
//         list = list->next;
//     }


// }