/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:42 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:52 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_cd_help_part_1(void)
{
	ft_putendl_fd("cd: cd [-L|[-P [-e]] [-@]] [dir]", 1);
	ft_putendl_fd("    Change the shell working directory.", 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("    Change the current directory to DIR.", 1);
	ft_putendl_fd("   The default DIR is the value of the", 1);
	ft_putstr_fd("    HOME shell variable. If DIR is \"-\"", 1);
	ft_putendl_fd(", it is converted to $OLDPWD.", 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("    The variable CDPATH defines the search ", 1);
	ft_putendl_fd("path for the directory containing", 1);
	ft_putstr_fd("    DIR.  Alternative directory names in ", 1);
	ft_putendl_fd("CDPATH are separated by a colon (:).", 1);
	ft_putstr_fd("    A null directory name is the same as ", 1);
	ft_putendl_fd("the current directory.  If DIR begins", 1);
	ft_putendl_fd("    with a slash (/), then CDPATH is not used.", 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("    If the directory is not found, and the ", 1);
	ft_putendl_fd("shell option `cdable_vars' is set,", 1);
	ft_putstr_fd("    the word is assumed to be  a variable", 1);
	ft_putendl_fd(" name.  If that variable has a value,", 1);
	ft_putendl_fd("    its value is used for DIR.", 1);
	ft_putendl_fd("", 1);
	print_cd_help_part_2();
}

char	*get_depending_path(t_shell *shell, char *goal)
{
	char	*path;

	path = get_env_value(goal, shell->env);
	if (!path || path[0] == '\0')
	{
		free(path);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(goal, 2);
		ft_putendl_fd(" not set", 2);
		return (NULL);
	}
	if (ft_strncmp(goal, "OLDPWD", 7) == 0)
		ft_putendl_fd(path, 1);
	return (path);
}

char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->args || !shell)
		return (NULL);
	if (!cmd->args[1])
		path = get_depending_path(shell, "HOME");
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		path = get_depending_path(shell, "OLDPWD");
	else if (ft_strncmp(cmd->args[1], "~", 2) == 0)
		path = get_depending_path(shell, "HOME");
	else if (ft_strncmp(cmd->args[1], "--help", 7) == 0)
	{
		print_cd_help_part_1();
		return (NULL);
	}
	else
		path = ft_strdup(cmd->args[1]);
	return (path);
}

char	*get_pwd_safe(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_env_value("PWD", shell->env);
	if (pwd && pwd[0] == '\0')
	{
		free(pwd);
		return (NULL);
	}
	return (pwd);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*pwd;
	int		status;

	if (!cmd || !shell)
		return (1);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	pwd = get_pwd_safe(shell);
	path = get_cd_path(cmd, shell);
	if (!path)
	{
		free(pwd);
		return (1);
	}
	status = change_dir_and_update(shell, path, pwd);
	free(path);
	return (status);
}
