#include "builtin.h"

<<<<<<< HEAD
void handle_export_arg(char *arg, t_shell *shell)
{
    char *equal;
    char *key;
    char *value;

    if (arg[0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return;
    }
    equal = ft_strchr(arg, '=');
    if(equal)
        key = ft_substr(arg, 0, equal - arg);
    else
        key = ft_strdup(arg);
    value = get_value(arg, equal, shell);
    if (validate_identifier_export(key, value, equal))
        return;
    update_env_list(&shell->env, key, value);
    free(key);
    if (value && equal)
        free(value);
}

char *get_value(char *arg, char *equal, t_shell *shell)
{
    char *raw_value;

    (void)arg;
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

int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd || !shell)
        return (1);
    if (!cmd->args[1] || (ft_strncmp(cmd->args[1], "-p", 3) == 0 && !cmd->args[2]))
    {
        print_export_list(shell->env);
        return (0);
    }
    if (ft_strncmp(cmd->args[1], "-p", 3) == 0 && cmd->args[2])
        i = 2;
    else if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
        return (handle_export_n(cmd, shell));
    else if (cmd->args[1][0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return (2);
    }
    else
        i = 1;
    while (cmd->args[i])
        handle_export_arg(cmd->args[i++], shell);
    return (0);
}
=======
int	parse_export_options(char **args, int *i, int *flag_p, int *flag_n)
{
    int	ret;

    *flag_p = 0;
    *flag_n = 0;
    while (args && args[*i])
    {
        if (args[*i][0] != '-' || args[*i][1] == '\0')
            break;
        ret = is_only_pn_options(args[*i], flag_p, flag_n);
        if (ret == 2)
        {
            (*i)++;
            break;
        }
        if (ret == 0)
            return (0);
        (*i)++;
    }
    return (1);
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


int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	flag_p;
	int	flag_n;

	i = 1;
	if (!cmd || !shell)
		return (1);
	if (!cmd->args[1])
	{
		print_export_list(shell->env);
		return (0);
	}
	if (!parse_export_options(cmd->args, &i, &flag_p, &flag_n))
	{
		ft_putstr_fd("export: invalid option\n", 2);
		return (2);
	}
	if (!cmd->args[i] && (flag_p || (!flag_p && !flag_n)))
	{
		print_export_list(shell->env);
		return (0);
	}
	return (handle_export_flow(cmd, shell, i, flag_n));
}


>>>>>>> 5b98786 (built in)
