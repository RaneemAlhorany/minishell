#include "execution.h"

 char *extract_key(char *arg)
{
    char    *equal;
    char    *key;

    equal = ft_strchr(arg, '=');
    if (!equal)
        return (NULL);
    key = ft_substr(arg, 0, equal - arg);
    return (key);
}

 char *extract_value(char *arg)
{
    char    *equal;

    equal = ft_strchr(arg, '=');
    if (!equal)
        return (NULL);
    return (ft_strdup(equal + 1));
}

 int update_existing_node(t_env *node, char *key, char *value)
{
    if (node->value)
        free(node->value);
    node->value = value;
    node->has_value = 1;
    free(key);
    return (1);
}

int create_new_node(t_shell *shell, char *key, char *value)
{
    t_env *node;

    node = env_new(key, value);
    free(key);
    free(value);
    if (!node)
        return (0);
    node->is_exported = 0;
    env_add_back(&shell->env, node);
    return (1);
}

int set_shell_assignment(t_shell *shell, char *arg)
{
    t_env   *node;
    char    *key;
    char    *value;

    key = extract_key(arg);
    if (!key)
        return (0);
    value = extract_value(arg);
    if (!value)
        return (free(key), 0);
    node = find_env(shell->env, key);
    if (node)
        return (update_existing_node(node, key, value));
    return (create_new_node(shell, key, value));
}


