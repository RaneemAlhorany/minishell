#include "builtin.h"

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
