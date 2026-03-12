// edit +test


#include "builtin.h"

char *get_key(char *arg, char *equal)
{
    if (equal)
        return (ft_substr(arg, 0, equal - arg));
    return (ft_strdup(arg));
}

char *get_value(char *arg, char *equal, t_shell *shell)
{
    char *raw_value;

    if (!equal)
        return (get_env_value(arg, shell->env));

    raw_value = equal + 1;
    raw_value = remove_quotes(raw_value);
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


int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd->args[1])
    {
        print_export_list(shell->env);
        return (0);
    }

    i = 1;
    while (cmd->args[i])
    {
        handle_export_arg(cmd->args[i], shell);
        i++;
    }
    return (0);
}



// void handle_export_arg(char *arg, t_shell *shell)
// {
//     char *equal;
//     char *key;
//     char *raw_value;
//     char *value;

//     if (arg[0] == '-') // Check if the argument starts with '-'
//     {
//         ft_putstr_fd("export: invalid option\n", 2);
//         return;
//     }

//     equal = ft_strchr(arg, '=');
//     if (equal)
//     {
//         key = ft_substr(arg, 0, equal - arg);
//         raw_value = equal + 1;
//         if ((raw_value[0] == '"' && raw_value[ft_strlen(raw_value)-1] == '"') ||
//             (raw_value[0] == '\'' && raw_value[ft_strlen(raw_value)-1] == '\''))
//         {
//             raw_value[ft_strlen(raw_value)-1] = '\0';
//             raw_value++;
//         }
//         value = expand_string(raw_value, shell->env, shell->last_exit_status);
//     }
//     else
//     {
//         key = ft_strdup(arg);
//         value = get_env_value(key, shell->env); // Correct argument order
//     }

//     if (!is_valid_identifier(key))
//     {
//         ft_putstr_fd("export: not a valid identifier\n", 2);
//         free(key);
//         if (equal)
//             free(value);
//         return;
//     }
//     update_or_add_env(shell, key, value);
//     free(key);
//     if (value && equal) // Free only if value was newly allocated
//         free(value);
// }

