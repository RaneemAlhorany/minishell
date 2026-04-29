/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_handle1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:19 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:33:58 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	parse_export_arg(char *arg, char **key, char **value)
{
	if (assign_export_pair(key, value, arg))
		return (1);
	if (!is_valid_identifier(*key))
	{
		ft_putstr_fd("minishell : export: `", 2);
		if (*key && *key[0])
			ft_putstr_fd(*key, 2);
		else
			ft_putstr_fd(*value, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(*key);
		if (*value)
			free(*value);
		return (1);
	}
	return (0);
}

int	assign_export_pair(char **key, char **value, char *arg)
{
	char	*equal;

	*value = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		if (!*key)
			return (1);
		*value = ft_strdup(equal + 1);
		if (!*value)
		{
			free(*key);
			return (1);
		}
		return (0);
	}
	*key = ft_strdup(arg);
	if (!*key)
		return (1);
	return (0);
}

int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_export_n_logic(t_shell *shell, t_env *n, char *key, char *value)
{
	if (!n && !value)
	{
		remove_export_flag(shell, key);
		return ;
	}
	if (!n && value)
	{
		n = env_new(key, value);
		if (n)
		{
			n->is_exported = 0;
			n->has_value = 1;
			env_add_back(&shell->env, n);
		}
		return ;
	}
	if (!value)
		return ;
	if (n->value)
		free(n->value);
	n->value = ft_strdup(value);
	n->has_value = 1;
	n->is_exported = 0;
}

void	remove_export_flag(t_shell *shell, char *key)
{
	t_env	*node;
	char	*env_val;

	if (!shell || !key)
		return ;
	node = find_env(shell->env, key);
	if (node)
	{
		node->is_exported = 0;
		return ;
	}
	env_val = getenv(key);
	if (env_val)
	{
		node = env_new(key, env_val);
		if (!node)
			return ;
		node->is_exported = 0;
		node->has_value = 1;
		env_add_back(&shell->env, node);
	}
}
