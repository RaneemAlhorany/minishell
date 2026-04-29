/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:44 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:20:46 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_command(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free_redirections(cmd->redirections);
	free(cmd);
}

void	free_redirections(t_redirection *r)
{
	t_redirection	*tmp;

	while (r)
	{
		tmp = r->next;
		if (r->heredoc_fd >= 0)
			close(r->heredoc_fd);
		free(r->filename);
		free(r);
		r = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->prompt_prefix)
		free(shell->prompt_prefix);
	if (shell->env)
		free_env_list(shell->env);
	free(shell);
}

void	free_2d(char **dirs)
{
	int	i;

	if (!dirs)
		return ;
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
}
