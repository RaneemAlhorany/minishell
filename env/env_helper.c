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




void	update_env(t_shell *shell, char *key, char *value)//bablo edit
{
	t_env	*node;
	t_env	*new_node;

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
		return ;
	}
	new_node = create_env_node(key);
	if (!new_node)
		return ;
	if (value)
	{
		if (new_node->value)
			free(new_node->value);
		new_node->value = ft_strdup(value);
		new_node->has_value = 1;
	}
	else
	{
		if (new_node->value)
			free(new_node->value);
		new_node->value = NULL;
		new_node->has_value = 0;
	}
	env_add_back(&shell->env, new_node);
}

