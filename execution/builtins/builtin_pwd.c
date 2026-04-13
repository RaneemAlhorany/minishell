#include "builtin.h"

char	*get_pwd_value(char mode, t_shell *shell)
{
	char	*pwd;

	if (mode == 'P')
		pwd = getcwd(NULL, 0);
	else
	{
		pwd = get_env_value("PWD", shell->env);
		if (pwd && pwd[0] == '\0')
		{
			free(pwd);
			pwd = NULL;
		}
	}
	if (!pwd)
		pwd = getcwd(NULL, 0);
	return (pwd);
}

static int	update_pwd_mode(char c, char *mode)
{
	if (c == 'L' || c == 'P')
	{
		*mode = c;
		return (1);
	}
	ft_putendl_fd("pwd: invalid option", 2);
	ft_putendl_fd("pwd: usage: pwd [-LP]", 2);
	return (0);
}

static int	parse_pwd_option_arg(char *arg, char *mode)
{
	int	j;

	j = 1;
	while (arg[j])
	{
		if (!update_pwd_mode(arg[j], mode))
			return (0);
		j++;
	}
	return (1);
}


int	parse_pwd_options(t_cmd *cmd, char *mode)
{
	int	i;

	*mode = 'L';
	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		if (!parse_pwd_option_arg(cmd->args[i], mode))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_pwd(t_cmd *cmd, t_shell *shell)
{
	char	*pwd;
	char	mode;

	if (!parse_pwd_options(cmd, &mode))
		return (1);
	pwd = get_pwd_value(mode, shell);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
