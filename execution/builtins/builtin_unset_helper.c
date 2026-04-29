/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:56 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:18 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	process_unset_args(t_cmd *cmd, t_shell *shell, int i)
{
	char	*key;

	while (cmd->args[i])
	{
		key = ft_strtrim(cmd->args[i], "\"");
		if (key)
		{
			remove_env(shell, key);
			free(key);
		}
		i++;
	}
}

void	remove_env(t_shell *shell, char *key)
{
	t_env	*temp;
	t_env	*prev;

	if (!shell || !shell->env || !key)
		return ;
	temp = shell->env;
	prev = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev == NULL)
				shell->env = temp->next;
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
