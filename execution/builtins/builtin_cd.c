#include "builtin.h"

char *resolve_new_pwd(char *path, char *pwd)
{
    char *new_pwd;

    new_pwd = getcwd(NULL, 0);
    if (new_pwd)
        return (new_pwd);
    if (path[0] == '/')
        return (ft_strdup(path));
    if (pwd && pwd[0] != '\0')
    {
        if (ft_strncmp(path, "..", 3) == 0)
            return (get_parent_path(pwd));
        return (ft_strdup(pwd));
    }
    return (NULL);
}


int change_dir_and_update(t_shell *shell, char *path, char *pwd)
{
    char *new_pwd;

    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        free(pwd);
        return (1);
    }
    new_pwd = resolve_new_pwd(path, pwd);
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
char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd || !cmd->args || !shell)
		return (NULL);
	if (!cmd->args[1])
		path = get_depending_path(shell, "HOME");
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		path = get_depending_path(shell, "OLDPWD");
	else if (ft_strncmp(cmd->args[1], "~", 2) == 0)
		path = get_depending_path(shell, "HOME");
	else if (ft_strncmp(cmd->args[1], "--help", 7) == 0)
	{
		print_cd_help_part_1();
		return (NULL);
	}
	else
		path = expand_path(cmd->args[1], shell);
	return (path);
}




char *get_pwd_safe(t_shell *shell)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        pwd = get_env_value("PWD", shell->env);
    if (pwd && pwd[0] == '\0')
    {
        free(pwd);
        return (NULL);
    }
    return (pwd);
}

int builtin_cd(t_cmd *cmd, t_shell *shell)
{
    char    *path;
    char    *pwd;
    int     status;

    if (!cmd || !shell)
        return (1);
    if (cmd->args[1] && cmd->args[2])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (1);
    }
    pwd = get_pwd_safe(shell);
    path = get_cd_path(cmd, shell);
    if (!path)
    {
        free(pwd);
        return (1);
    }
    status = change_dir_and_update(shell, path, pwd);
    free(path);
    return (status);
}

