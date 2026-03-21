
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
<<<<<<< HEAD
=======
    if (!existing)
        return;
    existing->is_exported = 1;
>>>>>>> 5b98786 (built in)
    if (value)
    {
        if (existing->value)
            free(existing->value);
        existing->value = ft_strdup(value);
<<<<<<< HEAD
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

=======
        if (!existing->value)
            return;
        existing->has_value = 1;
    }
}


int  parse_char_flag(char **args, int *index , char character)
{
    int j;
    int flag;

    flag = 0;
    while (args[*index])
    {
        if (args[*index][0] != '-')
            break;
        if (args[*index][1] != character)
            break;
        j = 1;
        while (args[*index][j] == character)
            j++;

        if (args[*index][j] == '\0')
        {
            flag = 1;
            (*index)++;
        }
        else
            break;
    }
    return (flag);
}

>>>>>>> 5b98786 (built in)
