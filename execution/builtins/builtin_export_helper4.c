#include "builtin.h"

int	handle_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;

	if (arg[0] == '-')
	{
		ft_putstr_fd("export: invalid option\n", 2);
		return (1);
	}
	if (extract_export_data(arg, shell, &key, &value))
		return (1);
	update_env_list(&shell->env, key, value);
	free(key);
	if (value && ft_strchr(arg, '='))
		free(value);
	return (0);
}

static int	assign_export_key(char *arg, char *equal, char **key)
{
	if (equal)
		*key = ft_substr(arg, 0, equal - arg);
	else
		*key = ft_strdup(arg);
	if (!*key)
		return (1);
	return (0);
}

static int	assign_export_value(char *equal, char **key, char **value)
{
	if (!equal)
		return (0);
	*value = get_value(equal);
	if (!*value)
	{
		free(*key);
		return (1);
	}
	return (0);
}

int	extract_export_data(char *arg, t_shell *shell,char **key, char **value)
{
	char	*equal;
	(void)shell;

	equal = ft_strchr(arg, '=');
	*value = NULL;
	if (assign_export_key(arg, equal, key))
		return (1);
	if (assign_export_value(equal, key, value))
		return (1);
	if (validate_identifier_export(*key, *value, equal))
		return (1);
	return (0);
}

char *get_value(char *equal)
{
    char *raw_value;

    if (!equal)
        return (NULL);
    raw_value = equal + 1;
	return (ft_strdup(raw_value));
}

int validate_identifier_export(char *key, char *value, char *equal)
{
    if (!is_valid_identifier(key))
    {
        ft_putstr_fd("export: not a valid identifier\n", 2);
        free(key);
        if (equal)
            free(value);
        return (1);
    }
    return (0);
}


int	is_only_pn_options(const char *s, int *flag_p, int *flag_n)
{
    int	j;

    if (!s || s[0] != '-' || s[1] == '\0')
        return (0);
    if (ft_strncmp(s, "--", 3) == 0)
        return (2);
    j = 1;
    while (s[j])
    {
        if (s[j] == 'p')
            *flag_p = 1;
        else if (s[j] == 'n')
            *flag_n = 1;
        else
            return (0);
        j++;
    }
    return (1);
}
