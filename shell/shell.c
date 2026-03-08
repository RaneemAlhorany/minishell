
#include "minishell.h"

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
    shell -> is_running = 1; // Set the shell to running state
    shell -> last_exit_status = 0; // Initialize last exit status to 0

    return (shell);
}







