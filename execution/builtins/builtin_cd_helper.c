/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:37 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:33:47 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_cd_help_part_2(void)
{
	ft_putendl_fd("    Options:", 1);
	ft_putstr_fd("      -L        force symbolic links to be ", 1);
	ft_putendl_fd("followed: resolve symbolic", 1);
	ft_putstr_fd("                links in DIR after ", 1);
	ft_putendl_fd("processing instances of `..'", 1);
	ft_putstr_fd("      -P        use the physical directory", 1);
	ft_putendl_fd(" structure without following", 1);
	ft_putstr_fd("                symbolic links: resolve", 1);
	ft_putendl_fd(" symbolic links in DIR before", 1);
	ft_putendl_fd("                processing instances of `..'", 1);
	ft_putstr_fd("      -e        if the -P option is ", 1);
	ft_putendl_fd("supplied, and the current working", 1);
	ft_putstr_fd("                directory cannot be ", 1);
	ft_putendl_fd("determined successfully, exit with", 1);
	ft_putendl_fd("                a non-zero status", 1);
	ft_putstr_fd("      -@        on systems that support it", 1);
	print_cd_help_part_3();
}

void	print_cd_help_part_3(void)
{
	ft_putendl_fd(", present a file with extended", 1);
	ft_putstr_fd("                attributes as a directory", 1);
	ft_putendl_fd(" containing the file attributes", 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("    The default is to follow symbolic", 1);
	ft_putendl_fd(" links, as if `-L' were specified.", 1);
	ft_putstr_fd("    `..' is processed by removing the", 1);
	ft_putendl_fd(" immediately previous pathname component", 1);
	ft_putendl_fd("    back to a slash or the beginning of DIR.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    Exit Status:", 1);
	ft_putstr_fd("    Returns 0 if the directory is changed,", 1);
	ft_putendl_fd(" and if $PWD is set successfully when", 1);
	ft_putendl_fd("    -P is used; non-zero otherwise.", 1);
}

int	change_dir_and_update(t_shell *shell, char *path, char *pwd)
{
	char	*new_pwd;

	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(pwd);
		return (1);
	}
	new_pwd = resolve_new_pwd(path, pwd);
	if (!new_pwd)
	{
		free(pwd);
		return (1);
	}
	update_env(shell, "OLDPWD", pwd);
	update_env(shell, "PWD", new_pwd);
	free(pwd);
	free(new_pwd);
	return (0);
}

char	*resolve_new_pwd(char *path, char *pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		return (new_pwd);
	if (path[0] == '/')
		return (ft_strdup(path));
	if (pwd && pwd[0] != '\0')
	{
		if (ft_strncmp(path, "..", 3) == 0)
			return (get_parent_path(pwd));
		return (ft_strdup(pwd));
	}
	return (NULL);
}

char	*get_parent_path(char *pwd)
{
	int		i;
	char	*parent;

	if (!pwd || pwd[0] == '\0')
		return (NULL);
	i = ft_strlen(pwd) - 1;
	while (i > 0 && pwd[i] == '/')
		i--;
	while (i > 0 && pwd[i] != '/')
		i--;
	if (i == 0)
		return (ft_strdup("/"));
	parent = ft_substr(pwd, 0, i);
	return (parent);
}
