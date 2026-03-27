#include "minishell.h"

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

t_ast	*prepare_execution(t_shell *shell,char *line, t_token **tokens_head)
{
	char	*input;
	t_token	*tokens;

	if (!shell || !line || is_blank_line(line))
		return (NULL);
	input = ft_strdup(line);
	if (!input)
		return (NULL);
	tokens = lexer(input);
	free(input);
	if (!tokens)
		return (NULL);
	*tokens_head = tokens;
	if (!expand_tokens(tokens, shell))
		return (NULL);
	if (!syntax_check(tokens))
	{
		ft_putendl_fd("minishell: syntax error\n", 2);
		return (NULL);
	}
	return (parse_pipeline(&tokens));
}


int	execute_line(t_shell *shell,char *line)
{
	t_token	*tokens_head;
	t_ast	*ast;
	int		status;

	tokens_head = NULL;
	ast = prepare_execution(shell, line, &tokens_head);
	if (!ast)
	{
		if (tokens_head)
			free_tokens(tokens_head);
		return (1);
	}
	status = execute_ast(ast, shell);
	shell->last_exit_status = status;
	free_ast(ast);
	free_tokens(tokens_head);
	return (status);
}


void	shell_interactive(t_shell *shell)
{
	char	*line;

	while (shell && shell->is_running)
	{
		clear_last_signal();
		set_interactive_readline_mode(1);
		line = readline("minishell$ ");
		if (!line)
			break;		
		if (get_last_signal() == SIGINT)
		{
			shell->last_exit_status = 130;
			clear_last_signal();
		}
		if (line[0] != '\0')
		{
			add_history(line);
			set_interactive_readline_mode(0);
			shell->last_exit_status = execute_line(shell, line);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		exit_status;
	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
	{
		ft_putendl_fd("minishell: initialization failed\n", 2);
		return (1);
	}
	setup_signals();
	shell_interactive(shell);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	rl_clear_history();
	return (exit_status);
}
