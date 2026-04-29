/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:01 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:33:01 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_u_option(t_cmd *cmd, t_env **new_env, int *i)
{
	char	*arg;
	char	*unset_key;

	arg = cmd->args[*i];
	unset_key = NULL;
	if (arg[2] != '\0')
		unset_key = &arg[2];
	else if (cmd->args[*i + 1])
		unset_key = cmd->args[*i + 1];
	else
	{
		ft_putendl_fd("env: option requires an argument -- 'u'", 2);
		ft_putendl_fd("Try 'env --help' for more information.", 2);
		return (1);
	}
	if (*new_env)
		remove_env_entry(new_env, unset_key);
	if (arg[2] != '\0')
		(*i)++;
	else
		(*i) += 2;
	return (0);
}

int	process_option(t_cmd *cmd, t_env **new_env, int *i)
{
	char	*arg;

	arg = cmd->args[*i];
	if (ft_strncmp(arg, "--", 3) == 0)
	{
		(*i)++;
		return (1);
	}
	if (ft_strncmp(arg, "-i", 3) == 0)
	{
		free_env_list(*new_env);
		*new_env = NULL;
		(*i)++;
		return (0);
	}
	if (arg[0] == '-' && arg[1] == 'u')
		return (handle_u_option(cmd, new_env, i));
	if (arg[0] == '-' && arg[1] != '\0')
		return (print_env_invalid_option(arg));
	return (2);
}

t_env	*copy_env_list(t_env *env)
{
	t_env	*new_list;
	t_env	*new_node;
	t_env	*current;

	new_list = NULL;
	current = env;
	while (current)
	{
		new_node = env_new(current->key, current->value);
		if (!new_node)
		{
			free_env_list(new_list);
			return (NULL);
		}
		new_node->is_exported = current->is_exported;
		new_node->has_value = current->has_value;
		env_add_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}

int	handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i)
{
	int	status;

	*new_env = copy_env_list(shell->env);
	if (!*new_env)
		return (1);
	while (cmd->args[*i])
	{
		status = process_option(cmd, new_env, i);
		if (status == 1)
			break ;
		else if (status == 2)
			break ;
		else if (status != 0)
			return (status);
	}
	return (0);
}

int	builtin_env(t_cmd *cmd, t_shell *shell)
{
	t_env	*new_env;
	int		i;

	new_env = NULL;
	i = 1;
	if (!cmd || !shell)
		return (1);
	if (handle_option(cmd, shell, &new_env, &i))
	{
		if (new_env)
			free_env_list(new_env);
		return (1);
	}
	handle_env_assignments(cmd, &new_env, &i);
	if (cmd->args[i])
	{
		i = execute_env_command(cmd, shell, &new_env, i);
		if (new_env)
			free_env_list(new_env);
		return (i);
	}
	print_env(new_env);
	if (new_env)
		free_env_list(new_env);
	return (0);
}
