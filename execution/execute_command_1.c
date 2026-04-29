/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:16:34 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:28:38 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_assignment_word(char *arg)
{
	int	i;
	int	key_len;

	if (!arg)
		return (0);
	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	if (arg[key_len] != '=' || key_len == 0)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (i < key_len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_assignment_only_command(t_ast *n, t_shell *shell)
{
	int	i;

	if (!n->cmd->args || !n->cmd->args[0])
		return (-1);
	i = 0;
	while (n->cmd->args[i])
	{
		if (!is_assignment_word(n->cmd->args[i]))
			return (-1);
		i++;
	}
	if (handle_empty_command(n, shell) != 0)
		return (1);
	i = 0;
	while (n->cmd->args[i])
	{
		if (!set_shell_assignment(shell, n->cmd->args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	handle_empty_command(t_ast *node, t_shell *shell)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (save_stdin < 0 || save_stdout < 0)
	{
		if (save_stdin >= 0)
			close(save_stdin);
		if (save_stdout >= 0)
			close(save_stdout);
		return (1);
	}
	if (!apply_redirections(node->cmd->redirections, shell))
	{
		restore_fds(save_stdin, save_stdout);
		return (1);
	}
	restore_fds(save_stdin, save_stdout);
	return (0);
}

int	execute_command_node(t_ast *node, t_shell *shell)
{
	int	assignment_status;

	if (!node || !node->cmd)
		return (0);
	if (!node->cmd->args || !node->cmd->args[0])
		return (handle_empty_command(node, shell));
	if (node->cmd->args[0][0] == '\0' && !node->cmd->args[1])
		return (handle_empty_command(node, shell));
	assignment_status = handle_assignment_only_command(node, shell);
	if (assignment_status != -1)
		return (assignment_status);
	return (handle_command_execution(node, shell));
}
