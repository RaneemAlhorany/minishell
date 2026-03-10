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

char *strip_quotes(char *str)
{
    if (!str)
        return (NULL);
    return (ft_strtrim(str, "\""));
}

int builtin_unset(t_cmd *cmd, t_shell *shell)
{
    int i;
    char *key;

    if (!cmd || !shell)
        return (1);
    i = 1;
    /*
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        if (ft_strncmp(cmd->args[1], "-v", 3) == 0)
            i = 2;
        else
        {
            ft_putendl_fd("unset: %s: invalid option\n", cmd->args[1], 2);
            ft_putendl_fd("unset: usage: unset [-v] [name ...]\n", cmd->args[1], 2);
            return (1);
        }
    }*/
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        if (ft_strncmp(cmd->args[1], "-v", 3) == 0)
            i = 2;
        else
        {
            ft_putendl_fd("unset:invalid option", 2);
            ft_putendl_fd("unset: usage: unset [-v] [name ...]", 2);
            return (1);
        }
    }
    while (cmd->args[i])
    {
        key = strip_quotes(cmd->args[i]);
        if (key)
        {
            remove_env(shell, key);
            free(key);
        }
        i++;
    }
    return (0);
}
