#include "execution.h"

int is_assignment_word(char *arg)
{
    int i;
    int key_len;

    if (!arg)
        return (0);
    key_len = 0;
    while (arg[key_len] && arg[key_len] != '=')
        key_len++;
    if (arg[key_len] != '=' || key_len == 0)
        return (0);
    if (!ft_isalpha(arg[0]) && arg[0] != '_')
        return (0);
    i = 1;
    while (i < key_len)
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int set_shell_assignment(t_shell *shell, char *arg)
{
    t_env   *node;
    char    *equal;
    char    *key;
    char    *value;

    equal = ft_strchr(arg, '=');
    key = ft_substr(arg, 0, equal - arg);
    if (!key)
        return (0);
    value = ft_strdup(equal + 1);
    if (!value)
        return (free(key), 0);
    node = find_env(shell->env, key);
    if (node)
    {
        if (node->value)
            free(node->value);
        node->value = value;
        node->has_value = 1;
        free(key);
        return (1);
    }
    node = env_new(key, value);
    free(key);
    free(value);
    if (!node)
        return (0);
    node->is_exported = 0;
    env_add_back(&shell->env, node);
    return (1);
}

int handle_assignment_only_command(t_ast *node, t_shell *shell)
{
    int i;

    if (!node->cmd->args || !node->cmd->args[0])
        return (-1);
    i = 0;
    while (node->cmd->args[i])
    {
        if (!is_assignment_word(node->cmd->args[i]))
            return (-1);
        i++;
    }
    if (handle_empty_command(node, shell) != 0)
        return (1);
    i = 0;
    while (node->cmd->args[i])
    {
        if (!set_shell_assignment(shell, node->cmd->args[i]))
            return (1);
        i++;
    }
    return (0);
}

int	handle_dot_command(t_cmd *cmd)
{
    if (ft_strncmp(cmd->args[0], ".", 2) != 0)
        return (-1);
    if (cmd->args[1])
        return (-1);
    ft_putendl_fd("minishell: .: filename argument required", 2);
    ft_putendl_fd(".: usage: . filename [arguments]", 2);
    return (2);
}



int execute_builtin_with_redirection(t_ast *node, t_shell *shell, t_builtin_type type)
{
    int status;
    int save_stdin;
    int save_stdout;

    save_stdin = dup(STDIN_FILENO);
    save_stdout = dup(STDOUT_FILENO);

    if (!apply_redirections(node->cmd->redirections, shell))
    {
        restore_fds(save_stdin, save_stdout);
        return (1);
    }

    status = execute_builtin(node->cmd, shell, type);
    restore_fds(save_stdin, save_stdout);
    return (status);
}

int handle_empty_command(t_ast *node, t_shell *shell)
{
    int save_stdin;
    int save_stdout;

    save_stdin = dup(STDIN_FILENO);
    save_stdout = dup(STDOUT_FILENO);
    if (save_stdin < 0 || save_stdout < 0)
    {
        if (save_stdin >= 0)
            close(save_stdin);
        if (save_stdout >= 0)
            close(save_stdout);
        return (1);
    }

    if (!apply_redirections(node->cmd->redirections, shell))
    {
        restore_fds(save_stdin, save_stdout);
        return (1);
    }

    restore_fds(save_stdin, save_stdout);
    return (0);
}

int handle_command_execution(t_ast *node, t_shell *shell)
{
    t_builtin_type builtin_type;
    int            dot_status;

    if (!expand_cmd_wildcards(node->cmd))
        return (1);
    dot_status = handle_dot_command(node->cmd);
    if (dot_status != -1)
        return (dot_status);
    builtin_type = get_builtin_type(node->cmd->args[0]);
    if (builtin_type == BUILTIN_ENV && node->cmd->args[1])
        return (execute_external(node->cmd, shell));
    if (builtin_type != BUILTIN_NONE)
        return (execute_builtin_with_redirection(node, shell, builtin_type));
    return (execute_external(node->cmd, shell));
}



int execute_command_node(t_ast *node, t_shell *shell)
{
    int assignment_status;

    if (!node || !node->cmd)
        return (0);

    if (!node->cmd->args || !node->cmd->args[0])
        return (handle_empty_command(node, shell));
    if (node->cmd->args[0][0] == '\0' && !node->cmd->args[1])
        return (handle_empty_command(node, shell));

    assignment_status = handle_assignment_only_command(node, shell);
    if (assignment_status != -1)
        return (assignment_status);

    return (handle_command_execution(node, shell));
}
