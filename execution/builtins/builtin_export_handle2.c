/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_handle2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:23 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:15:25 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;

	if (arg[0] == '-')
	{
		ft_putstr_fd("minishell : export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	if (extract_export_data(arg, &key, &value))
		return (1);
	update_env_list(&shell->env, key, value);
	free(key);
	if (value && ft_strchr(arg, '='))
		free(value);
	return (0);
}

int	extract_export_data(char *arg, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	*value = NULL;
	if (assign_export_key(arg, equal, key))
		return (1);
	if (assign_export_value(equal, key, value))
		return (1);
	if (validate_identifier_export(*key, *value, equal))
		return (1);
	return (0);
}

int	assign_export_key(char *arg, char *equal, char **key)
{
	if (equal)
		*key = ft_substr(arg, 0, equal - arg);
	else
		*key = ft_strdup(arg);
	if (!*key)
		return (1);
	return (0);
}

int	assign_export_value(char *equal, char **key, char **value)
{
	if (!equal)
		return (0);
	*value = ft_strdup(equal + 1);
	if (!*value)
	{
		free(*key);
		return (1);
	}
	return (0);
}

int	validate_identifier_export(char *key, char *value, char *equal)
{
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell : export: `", 2);
		if (key && key[0])
			ft_putstr_fd(key, 2);
		else
			ft_putstr_fd(value, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(key);
		if (equal)
			free(value);
		return (1);
	}
	return (0);
}
