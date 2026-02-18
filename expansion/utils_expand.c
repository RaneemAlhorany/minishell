
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


char    *expand_var(char *input, int *i, t_env *env, int last_status)
{
    int     start;
    char    *var_name;
    char    *value;

    (*i)++; // skip '$'
    if (input[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(last_status));
    }
    if (!ft_isalpha(input[*i]) && input[*i] != '_')
    {
        (*i)--;  // important fix
        return (ft_strdup("$"));
    }
    start = *i;
    while (ft_isalnum(input[*i]) || input[*i] == '_')
        (*i)++;
    var_name = ft_substr(input, start, (*i - start));
    if (!var_name)
        return (NULL);
    value = get_env_value(var_name, env);
    free(var_name);
    return (value);
}


 void cleanup_expand(t_expand *ex)
{
    free(ex->buf.data);
}




