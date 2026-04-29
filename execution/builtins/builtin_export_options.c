/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_options.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:32 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:15:35 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	parse_export_options(char **args, int *i, int *flag_p, int *flag_n)
{
	int	ret;

	*flag_p = 0;
	*flag_n = 0;
	while (args && args[*i])
	{
		if (args[*i][0] != '-' || args[*i][1] == '\0')
			break ;
		ret = is_only_pn_options(args[*i], flag_p, flag_n);
		if (ret == 2)
		{
			(*i)++;
			break ;
		}
		if (ret == 0)
			return (0);
		(*i)++;
	}
	return (1);
}

int	is_only_pn_options(const char *s, int *flag_p, int *flag_n)
{
	int	j;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (0);
	if (ft_strncmp(s, "--", 3) == 0)
		return (2);
	j = 1;
	while (s[j])
	{
		if (s[j] == 'p')
			*flag_p = 1;
		else if (s[j] == 'n')
			*flag_n = 1;
		else
			return (0);
		j++;
	}
	return (1);
}

int	error_export_arg(t_cmd *cmd, int i)
{
	ft_putstr_fd("minishell : export:", 2);
	ft_putstr_fd(cmd->args[i], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("export: usage: export [-fn] [name[=value] ...] or export -p",
		2);
	return (2);
}

int	handle_export_flow(t_cmd *cmd, t_shell *shell, int i, int flag_n)
{
	int	status;

	status = 0;
	if (!cmd->args[i])
	{
		print_export_list(shell->env);
		return (0);
	}
	if (flag_n)
		return (handle_export_n(cmd, shell, i));
	while (cmd->args[i])
	{
		if (handle_export_arg(cmd->args[i], shell))
			status = 1;
		i++;
	}
	return (status);
}

int	handle_export_n(t_cmd *cmd, t_shell *shell, int i)
{
	int		error;
	char	*key;
	char	*value;
	t_env	*node;

	error = 0;
	while (cmd->args[i])
	{
		if (parse_export_arg(cmd->args[i], &key, &value))
			error = 1;
		else
		{
			node = find_env(shell->env, key);
			handle_export_n_logic(shell, node, key, value);
		}
		free(key);
		if (value)
			free(value);
		i++;
	}
	return (error);
}
