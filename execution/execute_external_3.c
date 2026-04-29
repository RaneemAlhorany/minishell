/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:02 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:30:32 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

void	print_command_not_found(char *cmd)
{
	const char	*prefix;
	const char	*suffix;
	char		*line;

	prefix = "minishell: ";
	suffix = ": command not found\n";
	line = build_error_line(prefix, cmd, suffix);
	if (!line)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	ft_putstr_fd(line, 2);
	free(line);
}

char	*build_error_line(const char *prefix, const char *name,
		const char *suffix)
{
	char	*line;
	size_t	len;

	len = ft_strlen(prefix) + ft_strlen(name) + ft_strlen(suffix);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, prefix, ft_strlen(prefix));
	ft_memcpy(line + ft_strlen(prefix), name, ft_strlen(name));
	ft_memcpy(line + ft_strlen(prefix) + ft_strlen(name), suffix,
		ft_strlen(suffix));
	line[len] = '\0';
	return (line);
}

int	validate_command_access(char *cmd_path, t_cmd *cmd)
{
	t_stat	file_stat;

	if (stat(cmd_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd->args[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	if (access(cmd_path, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->args[0]);
		if (errno == ENOENT)
			return (127);
		return (126);
	}
	return (0);
}

int	is_minishell_command(char *cmd)
{
	char	*base;

	if (!cmd)
		return (0);
	base = ft_strrchr(cmd, '/');
	if (base)
		base++;
	else
		base = cmd;
	return (ft_strlen(base) == 9 && ft_strncmp(base, "minishell", 9) == 0);
}
