#include "env.h"


int count_valid_env(t_env *env)
{
    int count = 0;

    while (env)
    {
        if (env->is_exported && env->has_value)
            count++;
        env = env->next;
    }
    return count;
}


char *build_env_line(t_env *env)
{
    char *tmp;
    char *line;

    tmp = ft_strjoin(env->key, "=");
    if (!tmp)
        return NULL;

    line = ft_strjoin(tmp, env->value ? env->value : "");
    free(tmp);

    return line;
}


void free_envp_partial(char **envp, int i)
{
    while (i--)
        free(envp[i]);
    free(envp);
}


char **env_list_to_envp(t_env *env)
{
    char    **envp;
    int     len;
    int     i;

    len = count_valid_env(env);
    envp = malloc(sizeof(char *) * (len + 1));
    if (!envp)
        return NULL;
    i = 0;
    while (env)
    {
        if (env->is_exported && env->has_value)
        {
            envp[i] = build_env_line(env);
            if (!envp[i])
            {
                free_envp_partial(envp, i);
                return NULL;
            }
            i++;
        }
        env = env->next;
    }
    envp[i] = NULL;
    return envp;
}

