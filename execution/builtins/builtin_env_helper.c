
#include "builtin.h"


void handle_env_assignments(t_cmd *cmd, t_env **new_env, int *i)
{
    while (cmd->args[*i] && ft_strchr(cmd->args[*i], '='))
    {
        char *key = ft_substr(cmd->args[*i], 0,
                ft_strchr(cmd->args[*i], '=') - cmd->args[*i]);
        char *value = ft_strdup(ft_strchr(cmd->args[*i], '=') + 1);

        update_env_list(new_env, key, value);

        free(key);
        free(value);
        (*i)++;
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

void print_env(t_env *env)//bablo edit
{
    while (env)
    {
        if (env->key && env->has_value)
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
