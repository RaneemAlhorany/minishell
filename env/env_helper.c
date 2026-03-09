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




void	update_env(t_shell *shell, char *key, char *value)
{
	t_env	*node;
	t_env	*new_node;

	node = find_env(shell->env, key);
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
		return ;
	}
	new_node = create_env_node(key);
	if (!new_node)
		return ;
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	env_add_back(&shell->env, new_node);
}

