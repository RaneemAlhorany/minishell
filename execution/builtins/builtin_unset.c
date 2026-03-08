// edit +test


#include "builtin.h"



void remove_env(t_shell *shell, char *key)
{
    t_env *temp;
    t_env *prev;

    if (!shell || !shell->env || !key)
        return;
    temp = shell -> env;
    prev = NULL;
    while (temp)
    {
        if (ft_strncmp(temp -> key , key , ft_strlen(key)+1) == 0)
        {
            if (prev == NULL)
                shell ->env = temp ->next;
            else 
                prev -> next = temp -> next;
            free(temp ->key);
            if (temp->value)
                free(temp->value);
            free(temp);
            return ;
        }
        prev = temp;
        temp = temp ->next;
    }
}




int builtin_unset(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd || !shell)
        return (1);
    i = 1;
    while (cmd->args[i])
    {
        remove_env(shell , cmd->args[i] );
        i++;
    }
    return (0);
}
