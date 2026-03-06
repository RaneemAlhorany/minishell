#include "builtin.h"

char *get_cd_path(t_cmd *cmd, t_shell *shell)
{
    char *path;

    if (!cmd || !cmd->args || !shell)
        return (NULL);
    if (!cmd->args[1])
    {
        path = get_env_value("HOME", shell->env);
        if (!path)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return (NULL);
        }
    }
    else
        path = cmd->args[1];
    return (path);
}

int	change_dir_and_update(t_shell *shell, char *path, char *pwd)
{
	char	*new_pwd;

	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		free(pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(pwd);
		return (1);
	}
	update_env(shell, "OLDPWD", pwd);
	update_env(shell, "PWD", new_pwd);
	free(pwd);
	free(new_pwd);
	return (0);
}


int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*pwd;

	if (!cmd || !shell)
		return (1);

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);

	path = get_cd_path(cmd, shell);
	if (!path)
	{
		free(pwd);
		return (1);
	}

	return (change_dir_and_update(shell, path, pwd));
}


