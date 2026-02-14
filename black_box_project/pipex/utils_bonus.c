/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:10:52 by ralhoura          #+#    #+#             */
/*   Updated: 2026/01/22 15:48:26 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_pipex(t_pipex *px, char **argv, char **envp, int argc)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		px->is_here_doc = 1;
		px->limiter = argv[2];
		px->infile = NULL;
	}
	else
	{
		px->is_here_doc = 0;
		px->limiter = NULL;
		px->infile = argv[1];
	}
	px->envp = envp;
	px->infile_fd = -1;
	px->outfile_fd = -1;
	px->outfile = argv[argc - 1];
}

char	*get_path_from_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_cmd_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*search_in_paths(char *cmd, char *path)
{
	char	**paths;
	char	*full;
	int		i;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = build_cmd_path(paths[i], cmd);
		if (full)
		{
			free_cmds(paths);
			return (full);
		}
		i++;
	}
	free_cmds(paths);
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	*path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	return (search_in_paths(cmd, path));
}
