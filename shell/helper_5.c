#include "shell.h"



#include "shell.h"

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

void	handle_sigint(t_shell *shell)
{
	if (get_last_signal() == SIGINT)
	{
		shell->last_exit_status = 130;
		clear_last_signal();
	}
}

void	process_line(t_shell *shell, char *line)
{
	if (line[0] != '\0')
	{
		add_history(line);
		set_interactive_readline_mode(0);
		shell->last_exit_status = execute_line(shell, line);
		if (get_last_signal() == SIGQUIT)
		{
			ft_putendl_fd("Quit (core dumped)", 2);
			clear_last_signal();
		}
	}
}



void	shell_interactive(t_shell *shell)
{
	char	*line;
	char	*prompt;

	while (shell && shell->is_running)
	{
		clear_last_signal();
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
		process_line(shell, line);
		free(line);
	}
}