
#include "builtin.h"

void update_env_list(t_env **env, char *key, char *value)
{
    t_env *existing;
    t_env *new_node;

    if (!env || !key)
        return;
    existing = find_env(*env, key);
    if (existing)
        handle_existing(existing, value);
    else
    {
        new_node = env_new(key, value);
        if (!new_node)
            return;
        env_add_back(env, new_node);
    }
}

void handle_existing(t_env *existing, char *value)
{
    if (value)
    {
        if (existing->value)
            free(existing->value);
        existing->value = ft_strdup(value);
        existing->has_value = 1;
        existing->is_exported = 1;
    }
    else if (!existing->has_value)
    {
        if (existing->value)
            free(existing->value);
        existing->value = NULL;
        existing->has_value = 0;
    }
}

