
#include "builtin.h"

int	is_echo_n_option(const char *arg)
{
    int	j;

    if (!arg || arg[0] != '-' || arg[1] == '\0')
        return (0);
    j = 1;
    while (arg[j])
    {
        if (arg[j] != 'n')
            return (0);
        j++;
    }
    return (1);
}

void update_env_list(t_env **env, char *key, char *value)
{
    t_env *existing;
    t_env *new_node;

    if (!env || !key)
        return;
    existing = find_env(*env, key);
    if (existing)
        handle_existing(existing, value);
    else
    {
        new_node = env_new(key, value);
        if (!new_node)
            return;
        env_add_back(env, new_node);
    }
}

void handle_existing(t_env *existing, char *value)
{
    if (!existing)
        return;
    existing->is_exported = 1;
    if (value)
    {
        if (existing->value)
            free(existing->value);
        existing->value = ft_strdup(value);
        if (!existing->value)
            return;
        existing->has_value = 1;
    }
}

static int	is_matching_flag_arg(char *arg, char character)
{
	if (character == 'n' && !is_echo_n_option(arg))
		return (0);
	if (arg[0] != '-')
		return (0);
	if (arg[1] != character)
		return (0);
	return (1);
}

static int	consume_char_flag(char *arg, int *flag, char character)
{
	int	j;

	j = 1;
	while (arg[j] == character)
		j++;
	if (arg[j] != '\0')
		return (0);
	*flag = 1;
	return (1);
}


int  parse_char_flag(char **args, int *index , char character)
{
    int flag;

    flag = 0;
    while (args[*index])
    {
        if (!is_matching_flag_arg(args[*index], character))
            break;
        if (!consume_char_flag(args[*index], &flag, character))
            break;
		(*index)++;
    }
    return (flag);
}

