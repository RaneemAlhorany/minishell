




t_env *find_env(t_env *env, char *key)
{
    t_env *temp;

    if (!env || !key)
        return (NULL);
    temp = env;
    while (temp)
    {
        if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}



