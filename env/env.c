#include "env.h"

char **env_list_to_envp(t_env *env)
{
    int        i;
    int        len;
    t_env      *cur;
    char       **envp;
    char       *line;

    len = 0;
    cur = env;
    while (cur)
    {
        if (cur->is_exported && cur->has_value)
            len++;
        cur = cur->next;
    }
    envp = malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return (NULL);
    i = 0;
    cur = env;
    while (cur)
    {
        if (cur->is_exported && cur->has_value)
        {
            line = ft_strjoin(cur->key, "=");
            if (!line)
                break;
            envp[i] = ft_strjoin(line, cur->value ? cur->value : "");
            free(line);
            if (!envp[i])
                break;
            i++;
        }
        cur = cur->next;
    }
    if (i != len)
    {
        while (i--)
            free(envp[i]);
        free(envp);
        return (NULL);
    }
    envp[i] = NULL;
    return (envp);
}