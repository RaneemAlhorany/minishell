
#include "builtin.h"


int	is_visible_export(t_env *env)
{
	if (!env || !env->key || !env->is_exported)
		return (0);
	if (ft_strncmp(env->key, "_", 2) == 0)
		return (0);
	return (1);
}


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


int	parse_export_options(char **args, int *i, int *flag_p, int *flag_n)
{
    int	ret;

    *flag_p = 0;
    *flag_n = 0;
    while (args && args[*i])
    {
        if (args[*i][0] != '-' || args[*i][1] == '\0')
            break;
        ret = is_only_pn_options(args[*i], flag_p, flag_n);
        if (ret == 2)
        {
            (*i)++;
            break;
        }
        if (ret == 0)
            return (0);
        (*i)++;
    }
    return (1);
}


