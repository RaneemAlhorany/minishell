
#include "builtin.h"

void	apply_export_n(t_shell *shell, char *key, char *value)
{
	t_env	*node;

	node = find_env(shell->env, key);
	handle_export_n_logic(shell, node, key, value);
}

void	handle_export_n_logic(t_shell *shell, t_env *node, char *key, char *value)
{
	if (!node && !value)
	{
		remove_export_flag(shell, key);
		return;
	}
	if (!node && value)
	{
		node = env_new(key, value);
		if (node)
		{
			node->is_exported = 0;
			node->has_value = 1;
			env_add_back(&shell->env, node);
		}
		return;
	}
	if (value)
	{
		if (node->value)
			free(node->value);
		node->value = ft_strdup(value);
		node->has_value = 1;
	}
	node->is_exported = 0;
}

void remove_export_flag(t_shell *shell, char *key)
{
    t_env *node;
	char *env_val;

    if (!shell || !key)
        return;
    node = find_env(shell->env, key);
    if (node)
    {
        node->is_exported = 0;
        return;
    }
    env_val = getenv(key);
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



