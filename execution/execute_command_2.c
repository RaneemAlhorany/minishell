/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:42 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:31:19 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	set_shell_assignment(t_shell *shell, char *arg)
{
	t_env	*node;
	char	*key;
	char	*value;

	key = extract_key_or_value(arg, 1);
	if (!key)
		return (0);
	value = extract_key_or_value(arg, 0);
	if (!value)
	{
		free(key);
		return (0);
	}
	node = find_env(shell->env, key);
	if (node)
	{
		if (node->value)
			free(node->value);
		node->value = value;
		node->has_value = 1;
		free(key);
		return (1);
	}
	return (create_new_node(shell, key, value));
}

char	*extract_key_or_value(char *arg, int i)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	if (i)
		return (ft_substr(arg, 0, equal - arg));
	return (ft_strdup(equal + 1));
}

int	create_new_node(t_shell *shell, char *key, char *value)
{
	t_env	*node;

	node = env_new(key, value);
	free(key);
	free(value);
	if (!node)
		return (0);
	node->is_exported = 0;
	env_add_back(&shell->env, node);
	return (1);
}

int	handle_command_execution(t_ast *node, t_shell *shell)
{
	t_builtin_type	builtin_type;

	if (!expand_cmd_wildcards(node->cmd))
		return (1);
	if (!(ft_strncmp(node->cmd->args[0], ".", 2) != 0 || node->cmd->args[1]))
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		return (2);
	}
	builtin_type = get_builtin_type(node->cmd->args[0]);
	if (builtin_type != BUILTIN_NONE)
		return (execute_builtin_with_redirect(node, shell, builtin_type));
	return (execute_external(node->cmd, shell));
}
