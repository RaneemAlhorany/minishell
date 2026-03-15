
#include "builtin.h"



int is_valid_identifier(char *key)
{
    int i;

    if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
        return (0);
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}





void print_export_list(t_env *env)//bablo edit
{
    while (env)
    {
        if (env->key)
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(env->key, 1);
            if (env->has_value)
            {
                ft_putstr_fd("=\"", 1);
                if (env->value)
                    ft_putstr_fd(env->value, 1);
                ft_putstr_fd("\"", 1);
            }
            ft_putstr_fd("\n", 1);
        }
        env = env->next;
    }
}



void update_or_add_env(t_shell *shell, char *key, char *value)//bablo edit
{
    t_env *existing;
    t_env *new_node;

    existing = find_env(shell->env, key);
    if (existing)
    {
        if (value)
        {
            if (existing->value)
                free(existing->value);
            existing->value = ft_strdup(value);
            existing->has_value = 1;
        }
        else
        {
            if (!existing->has_value)
            {
                if (existing->value)
                    free(existing->value);
                existing->value = NULL;
                existing->has_value = 0;
            }
        }
    }
    else
    {
        new_node = env_new(key, value);
        if (!new_node)
            return ;
        env_add_back(&shell->env, new_node);
    }
}


int validate_identifier_export(char *key, char *value, char *equal)
{
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        free(key);
        if (equal)
            free(value);
        return (1);
    }
    return (0);
}
