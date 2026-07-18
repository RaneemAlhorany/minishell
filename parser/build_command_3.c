/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:57 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:19:58 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	enter_data(t_cmd *cmd, char ***new_args, int *new_cap)
{
	int	i;

	i = 0;
	while (i < cmd->arg_cap)
	{
		(*new_args)[i] = cmd->args[i];
		i++;
	}
	while (i < *new_cap)
	{
		(*new_args)[i] = NULL;
		i++;
	}
}

int	append_unquoted_words(t_cmd *cmd, t_token *token, int *index)
{
	char	*start;
	char	*word;

	start = token->value;
	if (!start)
	{
		return (0);
	}
	while (*start)
	{
		word = next_unquoted_word(&start);
		if (!word && *start)
			return (0);
		if (!word)
			break ;
		if (!ensure_cmd_args_capacity(cmd, *index))
		{
			free(word);
			return (0);
		}
		cmd->args[*index] = word;
		(*index)++;
	}
	return (1);
}

char	*next_unquoted_word(char **start)
{
	int		len;
	char	*word;

	while (**start == ' ' || **start == '\t' || **start == '\n')
		(*start)++;
	if (!**start)
		return (NULL);
	len = 0;
	while ((*start)[len] && (*start)[len] != ' ' && (*start)[len] != '\t'
		&& (*start)[len] != '\n')
		len++;
	word = ft_substr(*start, 0, len);
	*start += len;
	return (word);
}

int	handle_redirection_token(t_cmd *cmd, t_token **tokens, t_redirection **last)
{
	t_redirection	*new_redir;

	if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
		return (0);
	new_redir = create_redirection(*tokens);
	if (!new_redir)
		return (0);
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
		(*last)->next = new_redir;
	*last = new_redir;
	*tokens = (*tokens)->next;
	return (1);
}

t_redirection	*create_redirection(t_token *current)
{
	t_redirection	*new_redir;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->type = current->type;
	if (current->next)
		new_redir->quoted = current->next->quoted;
	else
		new_redir->quoted = 0;
	new_redir->heredoc_fd = -1;
	if (!current->next)
		new_redir->filename = NULL;
	else
		new_redir->filename = ft_strdup(current->next->value);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	return (new_redir);
}
