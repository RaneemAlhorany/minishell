/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:51 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:09 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_pwd_value(char mode, t_shell *shell)
{
	char	*pwd;

	if (mode == 'P')
		pwd = getcwd(NULL, 0);
	else
	{
		pwd = get_env_value("PWD", shell->env);
		if (pwd && pwd[0] == '\0')
		{
			free(pwd);
			pwd = NULL;
		}
	}
	if (!pwd)
		pwd = getcwd(NULL, 0);
	return (pwd);
}

int	parse_pwd_option_arg(char *arg, char *mode)
{
	int	j;

	j = 1;
	while (arg[j])
	{
		if (arg[j] == 'L' || arg[j] == 'P')
		{
			*mode = arg[j];
			return (1);
		}
		else
		{
			ft_putendl_fd("pwd: invalid option", 2);
			ft_putendl_fd("pwd: usage: pwd [-LP]", 2);
			return (0);
		}
		j++;
	}
	return (1);
}

int	parse_pwd_options(t_cmd *cmd, char *mode)
{
	int	i;

	*mode = 'L';
	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		if (!parse_pwd_option_arg(cmd->args[i], mode))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*pwd;
	char	mode;

	if (!parse_pwd_options(cmd, &mode))
		return (1);
	pwd = get_pwd_value(mode, shell);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
