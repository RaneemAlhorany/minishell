/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:21:08 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:21:10 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	execute_line(t_shell *shell, char *line)
{
	t_token	*tokens_head;
	t_ast	*ast;
	int		status;

	tokens_head = NULL;
	status = -1;
	ast = prepare_execution(shell, line, &tokens_head);
	shell->active_tokens = tokens_head;
	shell->active_ast = ast;
	if (!ast)
		return (handle_prepare_failure(shell, tokens_head));
	status = handle_heredoc_shell(shell, ast, tokens_head);
	if (status != -1)
		return (status);
	status = execute_and_update(shell, ast);
	shell->last_exit_status = status;
	cleanup_execution(shell, ast, tokens_head);
	return (status);
}

int	is_blank_input(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] != ' ' && line[index] != '\t')
			return (0);
		index++;
	}
	return (1);
}

void	process_line(t_shell *shell, char *line)
{
	int	status;

	if (line[0] == '\0' || is_blank_input(line))
		return ;
	add_history(line);
	set_interactive_readline_mode(0);
	status = execute_line(shell, line);
	shell->last_exit_status = status;
	if ((int)g_last_signal == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		g_last_signal = 0;
	}
}

char	*build_prompt(t_shell *shell)
{
	char	*prompt;

	if (shell->prompt_prefix)
	{
		prompt = ft_strjoin(shell->prompt_prefix, "minishell$ ");
		free(shell->prompt_prefix);
		shell->prompt_prefix = NULL;
		if (!prompt)
			return (ft_strdup("minishell$ "));
		return (prompt);
	}
	return (ft_strdup("minishell$ "));
}

void	shell_interactive(t_shell *shell)
{
	char	*line;
	char	*prompt;

	while (shell && shell->is_running)
	{
		g_last_signal = 0;
		set_interactive_readline_mode(1);
		prompt = build_prompt(shell);
		line = readline(prompt);
		free(prompt);
		handle_sigint(shell);
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		process_line(shell, line);
		free(line);
	}
}
