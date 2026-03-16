// edit +test

#include "builtin.h"

void update_env_list(t_env **env, char *key, char *value)//bablo edit
{
    t_env *existing;
    t_env *new_node;

    if (!env || !key)
        return;

    existing = find_env(*env, key);
    if (existing)
    {
        if (value)
        {
            free(existing->value);
            existing->value = ft_strdup(value);
            existing->has_value = 1;
            existing->is_exported = 1;
        }
        else if (!existing->has_value)
        {
            
            free(existing->value);
            existing->value = NULL;
            existing->has_value = 0;
        }
    }
    else
    {
        new_node = env_new(key, value);
        if (!new_node)
            return;
        env_add_back(env, new_node);
    }
}



int handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i)
{
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        if (ft_strncmp(cmd->args[1], "-i", 3) == 0)
        {
            *new_env = NULL;
            (*i)++;
        }
        else
        {
            ft_putendl_fd("invalid option", 2);
            return (1);
        }
    }
    else
        *new_env = shell->env;
    return (0);
}


int builtin_env(t_cmd *cmd, t_shell *shell)
{
    t_env *new_env = NULL;
    int i = 1;
    int status;

    if (!cmd || !shell)
        return (1);

    if (handle_option(cmd, shell, &new_env, &i))
        return (1);

    handle_env_assignments(cmd, &new_env, &i);

    status = handle_env_command_error(cmd, i);
    if (status)
        return (status);

    print_env(new_env);
    return (0);
}





// int builtin_env(t_cmd *cmd, t_shell *shell)
// {
//     t_env *temp_env;
//     t_env *new_env = NULL; 
//     int i = 1;

//     if (!cmd || !shell)
//         return (1);
//     if (cmd->args[1] && cmd->args[1][0] == '-')
//     {
//         if (ft_strncmp(cmd->args[1], "-i", 3) == 0)
//         {
//             new_env = NULL;
//             i++;
//         }
//         else
//         {
//             ft_putendl_fd("invalid option", 2);
//             return (1);
//         }
//     }
//     else
//         new_env = shell->env;
//     while (cmd->args[i] && ft_strchr(cmd->args[i], '='))// var=value arguments
//     {
//         char *key = ft_substr(cmd->args[i], 0, ft_strchr(cmd->args[i], '=') - cmd->args[i]);
//         char *value = ft_strdup(ft_strchr(cmd->args[i], '=') + 1);
//         update_env_list(&new_env, key, value);
//         free(key);
//         free(value);
//         i++;
//     }
//     if (cmd->args[i])
//     {
//         ft_putstr_fd("env: ‘", 2);
//         ft_putstr_fd(cmd->args[i], 2);
//         ft_putendl_fd("’: No such file or directory", 2);
//         return 127;
//     }
//     temp_env = new_env;
//     while (temp_env)
//     {
//         if (temp_env->key && temp_env->value)
//         {
//             ft_putstr_fd(temp_env->key, 1);
//             ft_putchar_fd('=', 1);
//             ft_putendl_fd(temp_env->value, 1);
//         }
//         temp_env = temp_env->next;
//     }
//     return (0);
// }





