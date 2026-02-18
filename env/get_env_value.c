#include "minishell.h"
char    *get_env_value(char *name, t_env *env)
{
    t_env   *temp;
    int len;

    if (!name )
        return (ft_strdup(""));

    temp = env;
    len = ft_strlen(name);
    while (temp)
    {
        if (ft_strncmp(name, temp->key, len + 1) == 0)
            return (ft_strdup(temp -> value));
        temp = temp -> next;
    }
    return (ft_strdup(""));
}

