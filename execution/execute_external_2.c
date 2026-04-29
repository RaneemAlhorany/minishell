/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:52 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:16:54 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	resolve_and_validate(t_cmd *cmd, t_shell *shell, char **cmd_path)
{
	int		path_available;
	int		status;
	char	*path_value;

	path_value = get_env_value("PATH", shell->env);
	if (!path_value || !*path_value)
		path_available = 0;
	else
		path_available = 1;
	free(path_value);
	*cmd_path = resolve_path_or_fail(cmd, shell, path_available);
	if (!*cmd_path)
		return (127);
	status = validate_command_access(*cmd_path, cmd);
	if (status)
		return (status);
	return (0);
}

char	*resolve_path_or_fail(t_cmd *cmd, t_shell *shell, int path_available)
{
	char	*cmd_path;

	cmd_path = resolve_command_path(cmd, shell);
	if (!cmd_path)
	{
		if (!ft_strchr(cmd->args[0], '/') && !path_available)
		{
			errno = ENOENT;
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->args[0]);
			return (NULL);
		}
		if (cmd_path)
			free(cmd_path);
		if (cmd->args[0] && *cmd->args[0])
			print_command_not_found(cmd->args[0]);
		else
			ft_putendl_fd("minishell: : command not found", 2);
		return (NULL);
	}
	return (cmd_path);
}

char	*resolve_command_path(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**dirs;

	if (ft_strchr(cmd->args[0], '/'))
		cmd_path = ft_strdup(cmd->args[0]);
	else
	{
		dirs = get_path_dirs(shell);
		if (!dirs)
			cmd_path = NULL;
		else
		{
			cmd_path = search_in_dirs(dirs, cmd->args[0]);
			free_2d(dirs);
		}
	}
	return (cmd_path);
}

char	**get_path_dirs(t_shell *shell)
{
	char	*path;
	char	**dirs;

	path = get_env_value("PATH", shell->env);
	if (!path || !*path)
	{
		free(path);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	free(path);
	return (dirs);
}

char	*search_in_dirs(char **dirs, char *name)
{
	char	*candidate;
	t_stat	file_stat;
	int		i;

	i = 0;
	while (dirs[i])
	{
		candidate = join_path(dirs[i], name);
		if (candidate && (access(candidate, X_OK) == 0) && (stat(candidate,
					&file_stat) == 0) && !(S_ISDIR(file_stat.st_mode)))
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}
