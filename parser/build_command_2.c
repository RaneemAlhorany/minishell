/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:19:52 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:19:53 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_command_tokens(t_ast *node, t_token **tokens, int *has_word)
{
	int				index;
	t_redirection	*last_redir;

	index = 0;
	last_redir = NULL;
	while (*tokens && !is_command_delimiter((*tokens)->type))
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			if (!handle_word_token(node->cmd, *tokens, &index))
				return (0);
			*has_word = 1;
		}
		else if (is_redirection((*tokens)->type))
		{
			if (!handle_redirection_token(node->cmd, tokens, &last_redir))
				return (0);
		}
		else
			return (0);
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	handle_word_token(t_cmd *cmd, t_token *token, int *index)
{
	if (*index == 0 && (get_reserved_word_1(token->value) != RW_NONE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	if (token->quoted)
	{
		if (!token->value)
			return (0);
		if (!ensure_cmd_args_capacity(cmd, *index))
			return (0);
		cmd->args[*index] = strdup(token->value);
		if (!cmd->args[*index])
			return (0);
		(*index)++;
		return (1);
	}
	return (append_unquoted_words(cmd, token, index));
}

t_reserved_word	get_reserved_word_1(const char *word)
{
	if (ft_strncmp(word, "in", 3) == 0 && word[2] == '\0')
		return (RW_IN);
	if (ft_strncmp(word, "do", 3) == 0 && word[2] == '\0')
		return (RW_DO);
	if (ft_strncmp(word, "done", 5) == 0 && word[4] == '\0')
		return (RW_DONE);
	if (ft_strncmp(word, "if", 3) == 0 && word[2] == '\0')
		return (RW_IF);
	if (ft_strncmp(word, "then", 5) == 0 && word[4] == '\0')
		return (RW_THEN);
	if (ft_strncmp(word, "elif", 5) == 0 && word[4] == '\0')
		return (RW_ELIF);
	if (ft_strncmp(word, "else", 5) == 0 && word[4] == '\0')
		return (RW_ELSE);
	if (ft_strncmp(word, "fi", 3) == 0 && word[2] == '\0')
		return (RW_FI);
	if (ft_strncmp(word, "while", 6) == 0 && word[5] == '\0')
		return (RW_WHILE);
	if (ft_strncmp(word, "until", 6) == 0 && word[5] == '\0')
		return (RW_UNTIL);
	return (get_reserved_word_2(word));
}

t_reserved_word	get_reserved_word_2(const char *word)
{
	if (ft_strncmp(word, "for", 4) == 0 && word[3] == '\0')
		return (RW_FOR);
	if (ft_strncmp(word, "case", 5) == 0 && word[4] == '\0')
		return (RW_CASE);
	if (ft_strncmp(word, "esac", 5) == 0 && word[4] == '\0')
		return (RW_ESAC);
	if (ft_strncmp(word, "select", 7) == 0 && word[6] == '\0')
		return (RW_SELECT);
	if (ft_strncmp(word, "function", 9) == 0 && word[8] == '\0')
		return (RW_FUNCTION);
	if (ft_strncmp(word, "{", 2) == 0 && word[1] == '\0')
		return (RW_LBRACE);
	if (ft_strncmp(word, "}", 2) == 0 && word[1] == '\0')
		return (RW_RBRACE);
	if (ft_strncmp(word, "[[", 3) == 0 && word[2] == '\0')
		return (RW_LBRACK2);
	if (ft_strncmp(word, "]]", 3) == 0 && word[2] == '\0')
		return (RW_RBRACK2);
	if (ft_strncmp(word, "!", 2) == 0 && word[1] == '\0')
		return (RW_BANG);
	return (RW_NONE);
}

int	ensure_cmd_args_capacity(t_cmd *cmd, int needed_index)
{
	char	**new_args;
	int		new_cap;

	if (!cmd || !cmd->args || cmd->arg_cap <= 0)
		return (0);
	if (needed_index + 1 < cmd->arg_cap)
		return (1);
	new_cap = cmd->arg_cap * 2;
	while (needed_index + 1 >= new_cap)
		new_cap *= 2;
	new_args = malloc(sizeof(char *) * new_cap);
	if (!new_args)
		return (0);
	enter_data(cmd, &new_args, &new_cap);
	free(cmd->args);
	cmd->args = new_args;
	cmd->arg_cap = new_cap;
	return (1);
}
