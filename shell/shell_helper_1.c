/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:52 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:41:05 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*root;

	if (!tokens || !*tokens)
		return (NULL);
	root = parse_and_expression(tokens);
	if (!root)
		return (NULL);
	if (*tokens)
	{
		free_ast(root);
		return (NULL);
	}
	return (root);
}

int	handle_heredoc_shell(t_shell *shell, t_ast *ast, t_token *tokens_head)
{
	int	preload_status;

	preload_status = preload_heredocs_ast(ast, shell);
	if (preload_status == -2)
	{
		shell->last_exit_status = 130;
		cleanup_execution(shell, ast, tokens_head);
		return (130);
	}
	if (preload_status != 0)
	{
		shell->last_exit_status = 1;
		cleanup_execution(shell, ast, tokens_head);
		return (1);
	}
	return (-1);
}

int	preload_heredocs_ast(t_ast *node, t_shell *shell)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (preload_heredocs_redirect(node->cmd->redirections,
				shell));
	if (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR || node->type == NODE_GROUP)
	{
		status = preload_heredocs_ast(node->s_pipe.left, shell);
		if (status != 0)
			return (status);
		if (node->type == NODE_GROUP)
			return (0);
		return (preload_heredocs_ast(node->s_pipe.right, shell));
	}
	return (0);
}

int	preload_heredocs_redirect(t_redirection *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			fd = handle_heredoc(redir, shell);
			if (fd == -2)
				return (-2);
			if (fd < 0)
				return (-1);
			redir->heredoc_fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

int	execute_and_update(t_shell *shell, t_ast *ast)
{
	char	*last_arg;
	int		status;

	last_arg = get_last_arg_from_ast(ast);
	if (last_arg)
		update_env(shell, "_", last_arg);
	status = execute_ast(ast, shell);
	return (status);
}
