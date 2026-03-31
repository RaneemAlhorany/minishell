#include "env.h"


int	init_env_value(t_env *node, char *value)
{
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
		node->has_value = 1;
	}
	else
	{
		node->value = NULL;
		node->has_value = 0;
	}
	return (0);
}


t_env	*env_new(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (init_env_value(new_node, value))
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}
	new_node->is_exported = 1;
	new_node->next = NULL;
	return (new_node);
}




void env_add_back(t_env **head, t_env *new)
{
    t_env *temp;

    if (!head || !new)
        return; // Handle null pointers
    if (*head == NULL)
    {
        *head = new;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}




t_env *create_env_node(char *env_str)
{
    char    *equal_sign;
    char    *key;
    char    *value_ptr;
    t_env   *new_node;

    equal_sign = ft_strchr(env_str, '=');
    if (equal_sign)
    {
        key = ft_substr(env_str, 0, equal_sign - env_str);
        value_ptr = equal_sign + 1;
    }
    else
    {
        key = ft_strdup(env_str);
        value_ptr = NULL;
    }
    if (!key)
        return (NULL);
    new_node = env_new(key, value_ptr);
    free(key);
    if (!new_node)
        return (NULL);
    return (new_node);
}


t_env *build_env_list(char **envp)
{
    t_env   *env_list;
    t_env   *new_node;
    int     i;

    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        new_node = create_env_node(envp[i]);
        if (!new_node)
        {
            free_env_list(env_list);
            return (NULL);
        }
        env_add_back(&env_list, new_node);
        i++;
    }
    return (env_list);
}


