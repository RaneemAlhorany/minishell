
#include "shell.h"

t_shell * init_shell(char **envp)
{
    t_shell *shell;

    shell = malloc(sizeof(t_shell));
    if (!shell)
        return NULL; // Handle memory allocation failure
    shell ->env = build_env_list(envp); // Initialize the environment pointer
    if (!shell->env)
    {
        free(shell);
        return (NULL);
    }
	shell->active_tokens = NULL;
	shell->active_ast = NULL;
    shell -> is_running = 1; // Set the shell to running state
    shell -> last_exit_status = 0; // Initialize last exit status to 0

    return (shell);
}


void	free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->env)
		free_env_list(shell->env);
	free(shell);
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




