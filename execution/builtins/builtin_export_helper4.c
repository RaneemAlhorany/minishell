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

int	extract_export_data(char *arg, t_shell *shell,char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	*value = NULL;
	if (equal)
		*key = ft_substr(arg, 0, equal - arg);
	else
		*key = ft_strdup(arg);
	if (!*key)
		return (1);
	if (equal)
	{
		*value = get_value(equal, shell);
		if (!*value)
		{
			free(*key);
			return (1);
		}
	}
	if (validate_identifier_export(*key, *value, equal))
		return (1);
	return (0);
}

char *get_value(char *equal, t_shell *shell)
{
    char *raw_value;

    if (!equal)
        return (NULL);
    raw_value = equal + 1;
    return (expand_string(raw_value, shell->env, shell->last_exit_status));
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
