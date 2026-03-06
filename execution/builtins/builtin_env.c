#include "builtin.h"



int builtin_env(t_cmd *cmd, t_shell *shell)
{
     t_env  *temp_env;
    if (!cmd || !shell)
        return (1);

    if (cmd->args[1])
        return (1);
    temp_env = shell -> env;
    while (temp_env)
    {
        if (temp_env ->key && temp_env ->value)
        {
            ft_putstr_fd(temp_env ->key , 1);
            ft_putchar_fd('=' , 1);
            ft_putendl_fd(temp_env->value , 1);
        }
        temp_env = temp_env -> next;
    }
    return (0);
}



