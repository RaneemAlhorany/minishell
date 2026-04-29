/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:13:59 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:24:54 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	add_new_env(t_shell *shell, char *key, char *value)
{
	t_env	*new_node;

	new_node = env_new(key, value);
	if (!new_node)
		return ;
	new_node->is_exported = 1;
	env_add_back(&shell->env, new_node);
}

t_env	*find_env(t_env *env, char *key)
{
	t_env	*temp;

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

	if (!shell || !key)
		return ;
	node = find_env(shell->env, key);
	if (node)
	{
		if (node->value)
			free(node->value);
		init_env_value(node, value);
		node->is_exported = 1;
		return ;
	}
	add_new_env(shell, key, value);
}
