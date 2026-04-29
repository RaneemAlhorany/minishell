/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:59 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:18:00 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	restore_fds(int stdin_copy, int stdout_copy)
{
	if (stdin_copy >= 0)
	{
		dup2(stdin_copy, STDIN_FILENO);
		close(stdin_copy);
	}
	if (stdout_copy >= 0)
	{
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
	}
}

void	free_str_array(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_parts(t_shell *shell)
{
	if (shell->active_tokens)
	{
		free_tokens(shell->active_tokens);
		shell->active_tokens = NULL;
	}
	if (shell->active_ast)
	{
		free_ast(shell->active_ast);
		shell->active_ast = NULL;
	}
}
