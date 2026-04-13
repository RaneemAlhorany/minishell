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

static int	append_envp_entry(char **envp, int *i, t_env *env)
{
    envp[*i] = build_env_line(env);
    if (!envp[*i])
        return (0);
    (*i)++;
    return (1);
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
        if (env->is_exported && env->has_value
            && !append_envp_entry(envp, &i, env))
            return (free_envp_partial(envp, i), NULL);
        env = env->next;
    }
    envp[i] = NULL;
    return envp;
}

