// edit +test


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


void print_export_list(t_env *env)
{
    while (env)
    {
        if (env->key)
        {
            ft_putstr_fd(env->key, 1);
            if (env->value)
            {
                ft_putstr_fd("=", 1);
                ft_putstr_fd(env->value, 1);
            }
            ft_putstr_fd("\n", 1);
        }
        env = env->next;
    }
}



void update_or_add_env(t_shell *shell, char *key, char *value)
{
    t_env *existing;
    t_env *new_node;

    existing = find_env(shell->env, key);
    if (existing)
    {
        if (existing->value)
            free(existing->value);
        if (value)
            existing->value =  ft_strdup(value);
        else 
            existing->value =  NULL;
    }
    else
    {
        new_node = env_new(key, value);
        if (!new_node)
            return ;
        env_add_back(&shell->env, new_node);
    }
}

void handle_export_arg(char *arg, t_shell *shell)
{
    char *equal;
    char *key;
    char *raw_value;
    char *value;

    equal = ft_strchr(arg, '=');
    if (equal)
    {
        key = ft_substr(arg, 0, equal - arg);
        raw_value = equal + 1;
        if ((raw_value[0] == '"' && raw_value[ft_strlen(raw_value)-1] == '"') ||
            (raw_value[0] == '\'' && raw_value[ft_strlen(raw_value)-1] == '\''))
        {
            raw_value[ft_strlen(raw_value)-1] = '\0';
            raw_value++;
        }
        value = expand_string(raw_value, shell->env, shell->last_exit_status);
    }
    else
    {
        key = ft_strdup(arg);
        value = NULL;
    }
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        free(key);
        if (equal)
            free(value);
        return;
    }
    update_or_add_env(shell, key, value);
    free(key);
    if (value)
        free(value);
}


int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd->args[1])
    {
        print_export_list(shell->env);
        return (0);
    }

    i = 1;
    while (cmd->args[i])
    {
        handle_export_arg(cmd->args[i], shell);
        i++;
    }
    return (0);
}
