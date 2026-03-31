#include "builtin.h"


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








