
#include "minishell.h"

 int  init_expand(t_expand *ex,char *input, t_env *env, int last_status)
{
    ex->input = input;
    ex->i = 0;
    ex->in_single = 0;
    ex->in_double = 0;
    ex->env = env;
    ex->last_status = last_status;
    if (!buffer_init(&ex->buf))
        return (0);
    return (1);
}



char *handle_special_dollar(char *input, int *i, int last_status)
{
    // $? 
    if (input[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(last_status));
    }
    if (input[*i] == '0')
    {
        (*i)++;
        return (ft_strdup("minishell"));
    }
    if (ft_isdigit(input[*i]))
    {
        (*i)++;
        return (ft_strdup(""));
    }
    if (input[*i] == '\0')
        return (ft_strdup("$"));
    if (!ft_isalpha(input[*i]) && input[*i] != '_')
        return (ft_strdup("$"));
    return (NULL); // not a special
}

char *handle_env_variable(char *input, int *i, t_env *env)
{
    int     start;
    char    *var_name;
    char    *value;

    start = *i;
    while (ft_isalnum(input[*i]) || input[*i] == '_')
        (*i)++;
    var_name = ft_substr(input, start, (*i - start));
    if (!var_name)
        return (NULL);
    value = get_env_value(var_name, env);
    free(var_name);
    if (!value)
        return (ft_strdup(""));
    return (value);
}



char *expand_var(char *input, int *i, t_env *env, int last_status)
{
    char *value;

    (*i)++; // skip '$'
    value = handle_special_dollar(input, i, last_status);
    if (value)
        return (value);
    return (handle_env_variable(input, i, env));
}





