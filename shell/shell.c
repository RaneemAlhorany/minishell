
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
	increment_shlvl(shell);

    return (shell);
}

 int get_current_level(t_env *shlvl_node)
{
    if (!shlvl_node || !shlvl_node->has_value
        || !is_str_numeric(shlvl_node->value))
        return (1);
    return (ft_atoi(shlvl_node->value));
}

void print_shlvl_warning(int level)
{
    ft_putstr_fd("minishell: warning: shell level (", 2);
    ft_putnbr_fd(level, 2);
    ft_putendl_fd(") too high, resetting to 1", 2);
}

int compute_next_level(int current_level)
{
    int next_level;

    next_level = current_level + 1;

    if (next_level < 0)
        return (0);
    if (next_level >= 1000)
    {
        print_shlvl_warning(next_level);
        return (1);
    }
    return (next_level);
}

void update_shlvl_value(t_shell *shell, int level)
{
    char *new_level;

    new_level = ft_itoa(level);
    if (!new_level)
        return ;
    update_env(shell, "SHLVL", new_level);
    free(new_level);
}






