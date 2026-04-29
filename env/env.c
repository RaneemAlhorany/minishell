/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:14:12 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:26:42 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*build_env_line(t_env *env)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(tmp, env->value);
	if (!line)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (line);
}

int	append_envp_entry(char **envp, int *i, t_env *env)
{
	envp[*i] = build_env_line(env);
	if (!envp[*i])
		return (0);
	(*i)++;
	return (1);
}

int	count_valid_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->is_exported && env->has_value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_list_to_envp(t_env *env)
{
	char	**envp;
	int		len;
	int		i;

	len = count_valid_env(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->is_exported && env->has_value && !append_envp_entry(envp, &i,
				env))
		{
			free_2d(envp);
			return (NULL);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
