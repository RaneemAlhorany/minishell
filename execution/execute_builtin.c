/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:29 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:29:32 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtin(t_cmd *cmd, t_shell *shell, t_builtin_type type)
{
	if (!cmd || !shell)
		return (0);
	if (type == BUILTIN_ECHO)
		return (builtin_echo(cmd, shell));
	else if (type == BUILTIN_CD)
		return (builtin_cd(cmd, shell));
	else if (type == BUILTIN_PWD)
		return (builtin_pwd(cmd, shell));
	else if (type == BUILTIN_EXPORT)
		return (builtin_export(cmd, shell));
	else if (type == BUILTIN_UNSET)
		return (builtin_unset(cmd, shell));
	else if (type == BUILTIN_ENV)
		return (builtin_env(cmd, shell));
	else if (type == BUILTIN_EXIT)
		return (builtin_exit(cmd, shell));
	return (0);
}

t_builtin_type	get_builtin_type(char *cmd)
{
	if (!cmd)
		return (BUILTIN_NONE);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (BUILTIN_ECHO);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (BUILTIN_CD);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (BUILTIN_PWD);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (BUILTIN_EXPORT);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (BUILTIN_UNSET);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (BUILTIN_ENV);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (BUILTIN_EXIT);
	else
		return (BUILTIN_NONE);
}
