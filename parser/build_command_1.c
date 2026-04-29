/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:47 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:19:49 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*build_command(t_token **tokens)
{
	t_ast	*node;
	int		has_word;

	has_word = 0;
	node = init_command_node(*tokens);
	if (!node)
		return (NULL);
	if (!process_command_tokens(node, tokens, &has_word) || (!has_word
			&& !node->cmd->redirections))
	{
		free_command(node->cmd);
		free(node);
		return (NULL);
	}
	return (node);
}

t_ast	*init_command_node(t_token *tokens)
{
	t_ast	*node;
	int		argc;

	node = create_ast_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	argc = count_words_in_cmd(tokens);
	node->cmd = create_cmd(argc);
	if (!node->cmd)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

int	count_words_in_cmd(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && !is_command_delimiter(tmp->type))
	{
		if (tmp->type == TOKEN_WORD)
		{
			if (tmp->quoted)
				count++;
			else
				count += count_unquoted_words(tmp->value);
		}
		else if (is_redirection(tmp->type))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (count);
}

int	count_unquoted_words(char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (!*s)
			break ;
		count++;
		while (*s && *s != ' ' && *s != '\t' && *s != '\n')
			s++;
	}
	return (count);
}

t_cmd	*create_cmd(int argc)
{
	t_cmd	*cmd;
	int		i;
	int		capacity;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_cap = 0;
	cmd->redirections = NULL;
	capacity = argc + 2;
	cmd->args = malloc(sizeof(char *) * capacity);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < capacity)
	{
		cmd->args[i] = NULL;
		i++;
	}
	cmd->arg_cap = capacity;
	return (cmd);
}
