#include "builtin.h"

char *get_key(char *arg, char *equal)
{
    if (equal)
        return (ft_substr(arg, 0, equal - arg));
    return (ft_strdup(arg));
}
//bablo edit
char *get_value(char *arg, char *equal, t_shell *shell)
{
    char *raw_value;

    (void)arg;
    if (!equal)
        return (NULL);
    raw_value = equal + 1;
    return (expand_string(raw_value, shell->env, shell->last_exit_status));
}

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
    key = get_key(arg, equal);
    value = get_value(arg, equal, shell);
    if (validate_identifier_export(key, value, equal))
        return;
    update_or_add_env(shell, key, value);
    free(key);
    if (value && equal)
        free(value);
}
//bablo edit
int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;
    int error;

    if (!cmd || !shell)
        return (1);

    if (!cmd->args[1] || (ft_strncmp(cmd->args[1], "-p", 3) == 0 && !cmd->args[2]))
    {
        print_export_list(shell->env);
        return (0);
    }
    if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
    {
        i = 2;
        error = 0;
        while (cmd->args[i])
        {
            if (!is_valid_identifier(cmd->args[i]))
            {
                ft_putstr_fd("export: not a valid identifier\n", 2);
                error = 1;
            }
            else
            {
                remove_export_flag(shell, cmd->args[i]);
            }
            i++;
        }
        return (error);
    }
    if (cmd->args[1][0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return (2);
    }
    i = 1;
    while (cmd->args[i])
    {
        handle_export_arg(cmd->args[i], shell);
        i++;
    }
    return (0);
}
