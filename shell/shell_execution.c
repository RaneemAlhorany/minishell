/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:34 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:22:36 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast	*prepare_execution(t_shell *shell, char *line, t_token **tokens_head)
{
	t_token	*tokens;
	char	*input;

	if (!shell)
		return (NULL);
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
	if (!line || is_blank_line(line))
		return (NULL);
	input = ft_strdup(line);
	if (!input)
		return (NULL);
	tokens = lexer(input);
	free(input);
	if (!tokens)
		return (NULL);
	*tokens_head = tokens;
	shell->active_tokens = tokens;
	if (!check_syntax(tokens, shell))
		return (NULL);
	if (!expand_tokens(tokens, shell))
		return (NULL);
	return (parse_pipeline(&tokens));
}

int	is_blank_line(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r')
			return (0);
		s++;
	}
	return (1);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	char	*unexpected;
	int		unexpected_newline;
	int		is_valid;

	unexpected = NULL;
	unexpected_newline = 0;
	is_valid = syntax_check(tokens, &unexpected, &unexpected_newline);
	if (!is_valid)
	{
		if (unexpected_newline)
		{
			if (!process_heredocs_on_error(tokens, shell))
				return (0);
		}
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		if (unexpected_newline)
			ft_putstr_fd("newline", 2);
		else if (unexpected)
			ft_putstr_fd(unexpected, 2);
		else
			ft_putstr_fd("newline", 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	return (1);
}

int	process_heredocs_on_error(t_token *tokens, t_shell *shell)
{
	t_token			*curr;
	t_redirection	redir;
	int				fd;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
		{
			redir.filename = curr->next->value;
			redir.next = NULL;
			redir.type = TOKEN_HEREDOC;
			redir.quoted = curr->next->quoted;
			redir.heredoc_fd = -1;
			fd = handle_heredoc(&redir, shell);
			if (fd >= 0)
				close(fd);
			if ((int)g_last_signal == SIGINT)
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*expanded;
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && (!prev
				|| (prev->type != TOKEN_REDIRECT_IN
					&& prev->type != TOKEN_REDIRECT_OUT
					&& prev->type != TOKEN_REDIRECT_APPEND
					&& prev->type != TOKEN_HEREDOC)))
		{
			expanded = expand_string(tokens->value, shell->env,
					shell->last_exit_status);
			if (!expanded)
				return (0);
			free(tokens->value);
			tokens->value = expanded;
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}
