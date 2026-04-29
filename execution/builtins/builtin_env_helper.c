/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:57 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:43 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	remove_env_entry(t_env **env, char *key)
{
	t_env	*temp;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;
	temp = *env;
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				*env = temp->next;
			else
				prev->next = temp->next;
			free(temp->key);
			if (temp->value)
				free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	print_env_invalid_option(const char *arg)
{
	ft_putstr_fd("env: invalid option -- '", 2);
	if (arg && arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putendl_fd("'", 2);
	ft_putendl_fd("Try 'env --help' for more information.", 2);
	return (1);
}

void	handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i)
{
	char	*key;
	char	*value;

	while (cmd->args[*i] && ft_strchr(cmd->args[*i], '='))
	{
		key = ft_substr(cmd->args[*i], 0, ft_strchr(cmd->args[*i], '=')
				- cmd->args[*i]);
		if (!key)
			break ;
		value = ft_strdup(ft_strchr(cmd->args[*i], '=') + 1);
		if (!value)
		{
			free(key);
			break ;
		}
		update_env_list(new_env, key, value);
		free(key);
		free(value);
		(*i)++;
	}
}

int	execute_env_command(t_cmd *cmd, t_shell *shell, t_env **new_env, int i)
{
	t_cmd			command;
	t_builtin_type	type;
	t_shell			temp_shell;
	char			*path_value;

	command = *cmd;
	command.args = &cmd->args[i];
	if (!command.args || !command.args[0])
		return (0);
	type = get_builtin_type(command.args[0]);
	if (type == BUILTIN_NONE && *new_env == NULL)
	{
		path_value = get_env_value("PATH", shell->env);
		*new_env = env_new("PATH", path_value);
		if (*new_env)
			(*new_env)->has_value = 1;
		if (path_value)
			free(path_value);
	}
	temp_shell = *shell;
	temp_shell.env = *new_env;
	if (type != BUILTIN_NONE)
		return (execute_builtin(&command, &temp_shell, type));
	return (execute_external(&command, &temp_shell));
}

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->is_exported && env->has_value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			if (env->value)
				ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}
