#include "builtin.h"

int handle_export_n(t_cmd *cmd, t_shell *shell)
{
    int     i;
    int     error;
    char    *key;
    char    *value;

    i = 2;
    error = 0;
    while (cmd->args[i])
    {
        if (parse_export_arg(cmd->args[i], &key, &value))
            error = 1;
        else
            apply_export_n(shell, key, value);
        free(key);
        if (value)
            free(value);
        i++;
    }
    return (error);
}

int parse_export_arg(char *arg, char **key, char **value)
{
    char *equal;

    *value = NULL;
    equal = ft_strchr(arg, '=');
    if (equal)
    {
        *key = ft_substr(arg, 0, equal - arg);
        *value = ft_strdup(equal + 1);
    }
    else
        *key = ft_strdup(arg);
    if (!*key || (equal && !*value))
        return (1);
    if (!is_valid_identifier(*key))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        return (1);
    }
    return (0);
}

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

void apply_export_n(t_shell *shell, char *key, char *value)
{
    t_env *node;

    node = find_env(shell->env, key);

    if (!node && value)
    {
        node = env_new(key, value);
        if (node)
        {
            node->is_exported = 0;
            node->has_value = 1;
            env_add_back(&shell->env, node);
        }
    }
    else
        remove_export_flag(shell, key);
}

void remove_export_flag(t_shell *shell, char *key)
{
    t_env *node;

    if (!shell || !key)
        return;
    node = find_env(shell->env, key);
    if (node)
    {
        node->is_exported = 0;
        return;
    }
    char *env_val = getenv(key);
    if (env_val)
    {
        node = env_new(key, env_val);
        if (!node)
            return;
        node->is_exported = 0;
        node->has_value = 1;
        env_add_back(&shell->env, node);
    }
}
