/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:39 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:40:59 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_prepare_failure(t_shell *shell, t_token *tokens_head)
{
	if (tokens_head)
		free_tokens(tokens_head);
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
	if ((int)g_last_signal == SIGINT)
		return (130);
	return (2);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	cleanup_execution(t_shell *shell, t_ast *ast, t_token *tokens)
{
	free_ast(ast);
	free_tokens(tokens);
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
	{
		free_command(ast->cmd);
	}
	else if (ast->type == NODE_PIPE || ast->type == NODE_AND
		|| ast->type == NODE_OR || ast->type == NODE_GROUP)
	{
		free_ast(ast->s_pipe.left);
		free_ast(ast->s_pipe.right);
	}
	free(ast);
}
