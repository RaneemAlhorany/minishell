#include "builtin.h"


int	handle_export_flow(t_cmd *cmd, t_shell *shell, int i, int flag_n)
{
	int	status;

	if (!cmd->args[i])
	{
		print_export_list(shell->env);
		return (0);
	}
	if (flag_n)
		return (handle_export_n(cmd, shell, i));
	status = 0;
	while (cmd->args[i])
	{
		if (handle_export_arg(cmd->args[i], shell))
			status = 1;
		i++;
	}
	return (status);
}

int handle_export_n(t_cmd *cmd, t_shell *shell,int i)
{
    int     error;
    char    *key;
    char    *value;

    error = 0;
    while (cmd->args[i])
    {
        if (parse_export_arg(cmd->args[i], &key, &value))
            error = 1;
        else
            apply_export_n(shell, key, value);
        free(key);
        if (value)
            free(value);
        i++;
    }
    return (error);
}

int	parse_export_arg(char *arg, char **key, char **value)
{
	if (extract_key_value(arg, key, value))
		return (1);
	if (!is_valid_identifier(*key))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		free(*key);
		if (*value)
			free(*value);
		return (1);
	}
	return (0);
}

static int	assign_export_pair(char **key, char **value, char *equal, char *arg)
{
	if (equal)
	{
		*key = ft_substr(arg, 0, equal - arg);
		if (!*key)
			return (1);
		*value = ft_strdup(equal + 1);
		if (!*value)
		{
			free(*key);
			return (1);
		}
		return (0);
	}
	*key = ft_strdup(arg);
	if (!*key)
		return (1);
	return (0);
}

int	extract_key_value(char *arg, char **key, char **value)
{
	char	*equal;

	*value = NULL;
	equal = ft_strchr(arg, '=');
	return (assign_export_pair(key, value, equal, arg));
}

int is_valid_identifier(char *key)
{
    int i;

    if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
        return (0);
    i = 1;
    while (key[i])
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }
    return (1);
}
