/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:23 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:22:31 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	compute_next_level(int current_level)
{
	int	next_level;

	next_level = current_level + 1;
	if (next_level < 0)
		return (0);
	if (next_level >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(next_level, 2);
		ft_putendl_fd(") too high, resetting to 1", 2);
		return (1);
	}
	return (next_level);
}

int	is_str_numeric(const char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	increment_shlvl(t_shell *shell)
{
	t_env	*shlvl_node;
	int		current_level;
	int		next_level;
	char	*new_level;

	if (!shell)
		return ;
	shlvl_node = find_env(shell->env, "SHLVL");
	if (!shlvl_node || !shlvl_node->has_value
		|| !is_str_numeric(shlvl_node->value))
		current_level = 1;
	else
		current_level = ft_atoi(shlvl_node->value);
	next_level = compute_next_level(current_level);
	new_level = ft_itoa(next_level);
	if (!new_level)
		return ;
	update_env(shell, "SHLVL", new_level);
	free(new_level);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = build_env_list(envp);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
	shell->in_child_process = 0;
	shell->is_running = 1;
	shell->last_exit_status = 0;
	shell->prompt_prefix = NULL;
	increment_shlvl(shell);
	return (shell);
}
