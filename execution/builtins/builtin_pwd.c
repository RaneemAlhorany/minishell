#include "builtin.h"

char	*get_pwd_value(char mode, t_shell *shell)
{
	char	*pwd;

	if (mode == 'P')
		pwd = getcwd(NULL, 0);
	else
		pwd = get_env_value("PWD", shell->env);
	if (!pwd)
		pwd = getcwd(NULL, 0);
	return (pwd);
}

int	parse_pwd_options(t_cmd *cmd, char *mode)
{
	int	i;
	int	j;

	*mode = 'L';
	i = 1;
	while (cmd->args[i] && cmd->args[i][0] == '-')
	{
		j = 1;
		while (cmd->args[i][j])
		{
			if (cmd->args[i][j] == 'L' || cmd->args[i][j] == 'P')
				*mode = cmd->args[i][j];
			else
			{
				ft_putendl_fd("pwd: invalid option", 2);
				ft_putendl_fd("pwd: usage: pwd [-LP]", 2);
				return (0);
			}
			j++;
		}
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
	if (mode == 'P')
		free(pwd);
	return (0);
}
