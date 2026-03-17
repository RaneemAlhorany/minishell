#include "builtin.h"

void handle_export_arg(char *arg, t_shell *shell)
{
    char *equal;
    char *key;
    char *value;

    if (arg[0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return;
    }
    equal = ft_strchr(arg, '=');
    if(equal)
        key = ft_substr(arg, 0, equal - arg);
    else
        key = ft_strdup(arg);
    value = get_value(arg, equal, shell);
    if (validate_identifier_export(key, value, equal))
        return;
    update_env_list(&shell->env, key, value);
    free(key);
    if (value && equal)
        free(value);
}

char *get_value(char *arg, char *equal, t_shell *shell)
{
    char *raw_value;

    (void)arg;
    if (!equal)
        return (NULL);
    raw_value = equal + 1;
    return (expand_string(raw_value, shell->env, shell->last_exit_status));
}

int validate_identifier_export(char *key, char *value, char *equal)
{
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        free(key);
        if (equal)
            free(value);
        return (1);
    }
    return (0);
}

int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd || !shell)
        return (1);
    if (!cmd->args[1] || (ft_strncmp(cmd->args[1], "-p", 3) == 0 && !cmd->args[2]))
    {
        print_export_list(shell->env);
        return (0);
    }
    if (ft_strncmp(cmd->args[1], "-p", 3) == 0 && cmd->args[2])
        i = 2;
    else if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
        return (handle_export_n(cmd, shell));
    else if (cmd->args[1][0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return (2);
    }
    else
        i = 1;
    while (cmd->args[i])
        handle_export_arg(cmd->args[i++], shell);
    return (0);
}
