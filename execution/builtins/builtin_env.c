#include "builtin.h"

<<<<<<< HEAD
=======
void print_env(t_env *env)
{
    while (env)
    {
        if (env->key && env->is_exported && env->has_value)
        {
            ft_putstr_fd(env->key, 1);
            ft_putchar_fd('=', 1);
            if (env->value)
                ft_putstr_fd(env->value, 1);
            ft_putchar_fd('\n', 1);
        }
        env = env->next;
    }
}

int handle_env_command_error(t_cmd *cmd, int i)
{
    if (cmd->args[i])
    {
        ft_putstr_fd("env: ‘", 2);
        ft_putstr_fd(cmd->args[i], 2);
        ft_putendl_fd("’: No such file or directory", 2);
        return (127);
    }
    return (0);
}

void handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i)
{
    char *key;
    char *value;

    while (cmd->args[*i] && ft_strchr(cmd->args[*i], '='))
    {
        key = ft_substr(cmd->args[*i], 0,
                ft_strchr(cmd->args[*i], '=') - cmd->args[*i]);
        if (!key)
            break;
        value = ft_strdup(ft_strchr(cmd->args[*i], '=') + 1);
        if (!value)
        {
            free(key);
            break;
        }
        update_env_list(new_env, key, value);
        free(key);
        free(value);
        (*i)++;
    }
}

int handle_option(t_cmd *cmd, t_shell *shell, t_env **new_env, int *i)
{
    int index;

    index =1;
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        
        if (parse_char_flag(cmd->args ,&index ,'i'))
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

>>>>>>> 5b98786 (built in)
int builtin_env(t_cmd *cmd, t_shell *shell)
{
    t_env *new_env;
    int i;
    int status;

    new_env = NULL;
    i = 1;
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
