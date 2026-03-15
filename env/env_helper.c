#include "env.h"


t_env *find_env(t_env *env, char *key)
{
    t_env *temp;

    if (!env || !key)
        return (NULL);
    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}



void    update_env(t_shell *shell, char *key, char *value)
{
    t_env    *node;
    t_env    *new_node;

    node = find_env(shell->env, key);
    if (node)
    {
        if (node->value)
            free(node->value);
        if (value)
        {
            node->value = ft_strdup(value);
            node->has_value = 1;
        }
        else
        {
            node->value = NULL;
            node->has_value = 0;
        }
        node->is_exported = 1;
        return ;
    }
    new_node = env_new(key, value);
    if (!new_node)
        return ;
    new_node->is_exported = 1;
    env_add_back(&shell->env, new_node);
}
