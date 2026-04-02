#include "builtin.h"

int	is_visible_export(t_env *env)
{
	if (!env || !env->key || !env->is_exported)
		return (0);
	if (ft_strncmp(env->key, "_", 2) == 0)
		return (0);
	return (1);
}

void print_export_list(t_env *env)
{
	t_env	**arr;
	int		count;
	int		i;

	count = count_exported(env);
	if (count == 0)
		return ;
	arr = collect_exported(env, count);
	if (!arr)
		return ;
	sort_env(arr, count);
	i = 0;
	while (i < count)
		print_one_env(arr[i++]);
	free(arr);
}

int count_exported(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (is_visible_export(env))
			count++;
		env = env->next;
	}
	return (count);
}

t_env **collect_exported(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (is_visible_export(env))
			arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

void sort_env(t_env **arr, int count)
{
    int i;
    int j;
    size_t len;
    t_env *tmp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strlen(arr[j]->key) > ft_strlen(arr[j + 1]->key))
                len = ft_strlen(arr[j]->key);
            else
                len = ft_strlen(arr[j + 1]->key);
            if (ft_strncmp(arr[j]->key, arr[j + 1]->key, len) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void print_one_env(t_env *node)
{
    ft_putstr_fd("declare -x ", 1);
    ft_putstr_fd(node->key, 1);
    if (node->has_value)
    {
        ft_putstr_fd("=\"", 1);
        if (node->value)
            ft_putstr_fd(node->value, 1);
        ft_putstr_fd("\"", 1);
    }
    ft_putstr_fd("\n", 1);
}
