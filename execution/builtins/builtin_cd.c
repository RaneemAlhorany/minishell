// #include "builtin.h"




// int change_dir_and_update(t_shell *shell, char *path, char *pwd)
// {
//     char *new_pwd;

//     if (chdir(path) != 0)
//     {
//         ft_putstr_fd("cd: ", 2);
//         perror(NULL);
//         ft_putstr_fd(": ", 2);
//         ft_putstr_fd(path, 2);
//         free(pwd);
//         return (1);
//     }
//     new_pwd = getcwd(NULL, 0);
//     if (!new_pwd)
//     {
//         free(pwd);
//         return (1);
//     }
//     update_env(shell, "OLDPWD", pwd);
//     update_env(shell, "PWD", new_pwd);
//     free(pwd);
//     free(new_pwd);
//     return (0);
// }

// char	*get_cd_path(t_cmd *cmd, t_shell *shell)
// {
// 	char	*path;

// 	if (!cmd || !cmd->args || !shell)
// 		return (NULL);
// 	if (!cmd->args[1])
// 		path = get_home_path(shell);
// 	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
// 		path = get_oldpwd_path(shell);
// 	else if (ft_strncmp(cmd->args[1], "~", 2) == 0)
// 		path = get_home_path(shell);
// 	else if (ft_strncmp(cmd->args[1], "--help", 7) == 0)
// 	{
// 		print_cd_help_part_1();
// 		return (NULL);
// 	}
// 	else
// 		path = expand_path(cmd->args[1], shell);
// 	return (path);
// }




// int builtin_cd(t_cmd *cmd, t_shell *shell)
// {
//     char *path;
//     char *pwd;

//     if (!cmd || !shell)
//         return (1);

//     if (cmd->args[1] && cmd->args[2])
//     {
//         ft_putendl_fd("cd: too many arguments", 2);
//         return (1);
//     }

//     pwd = getcwd(NULL, 0);
//     if (!pwd)
//         return (1);
//     path = get_cd_path(cmd, shell);
//     if (!path)
//     {
//         free(pwd);
//         return (1);
//     }
//     return (change_dir_and_update(shell, path, pwd));
// }





#include "builtin.h"


int change_dir_and_update(t_shell *shell, char *path, char *pwd)
{
    char *new_pwd;

    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        perror(NULL);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(path, 2);
        free(pwd);
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        char *env_pwd = get_env_value("PWD", shell->env);
        if (env_pwd)
            new_pwd = ft_strdup(env_pwd);
        else
            new_pwd = ft_strdup(path);
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
		path = get_home_path(shell);
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		path = get_oldpwd_path(shell);
	else if (ft_strncmp(cmd->args[1], "~", 2) == 0)
		path = get_home_path(shell);
	else if (ft_strncmp(cmd->args[1], "--help", 7) == 0)
	{
		print_cd_help_part_1();
		return (NULL);
	}
	else
		path = expand_path(cmd->args[1], shell);
	return (path);
}


int builtin_cd(t_cmd *cmd, t_shell *shell)
{
    char *path;
    char *pwd;

    if (!cmd || !shell)
        return (1);
    if (cmd->args[1] && cmd->args[2])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        char *env_pwd = get_env_value("PWD", shell->env);
        if (env_pwd)
            pwd = ft_strdup(env_pwd);
        else
            pwd = ft_strdup("");
    }
    path = get_cd_path(cmd, shell);
    if (!path)
    {
        free(pwd);
        return (1);
    }
    return (change_dir_and_update(shell, path, pwd));
}
