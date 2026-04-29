/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:16 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:16:19 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	update_env_list(t_env **env, char *key, char *value)
{
	t_env	*existing;
	t_env	*new_node;

	if (!env || !key)
		return ;
	existing = find_env(*env, key);
	if (existing)
		handle_existing(existing, value);
	else
	{
		new_node = env_new(key, value);
		if (!new_node)
			return ;
		env_add_back(env, new_node);
	}
}

void	handle_existing(t_env *existing, char *value)
{
	if (!existing)
		return ;
	existing->is_exported = 1;
	if (value)
	{
		if (existing->value)
			free(existing->value);
		existing->value = ft_strdup(value);
		if (!existing->value)
			return ;
		existing->has_value = 1;
	}
}
