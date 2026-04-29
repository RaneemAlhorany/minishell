/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:39 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:05 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_export_list(t_env *env)
{
	t_env	**arr;
	int		count;
	int		i;
	t_env	*cur;

	count = 0;
	i = 0;
	cur = env;
	while (cur)
	{
		if (cur->key && cur->is_exported && ft_strncmp(cur->key, "_", 2) != 0)
			count++;
		cur = cur->next;
	}
	if (count == 0)
		return ;
	arr = collect_exported(env, count);
	if (!arr)
		return ;
	sort_env(arr, count);
	while (i < count)
		print_one_env(arr[i++]);
	free(arr);
}

t_env	**collect_exported(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env && env->key && env->is_exported && ft_strncmp(env->key, "_",
				2) != 0)
			arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

void	sort_env(t_env **arr, int count)
{
	int		i;
	int		j;
	size_t	len;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strlen(arr[j]->key) > ft_strlen(arr[j + 1]->key))
				len = (ft_strlen(arr[j]->key));
			else
				len = (ft_strlen(arr[j + 1]->key));
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

void	print_one_env(t_env *node)
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
