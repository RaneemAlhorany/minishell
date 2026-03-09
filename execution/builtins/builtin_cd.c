// edit +test

#include "builtin.h"

char *expand_path(char *path, t_shell *shell)
{
    char *expanded;

    if (!path || !shell)
        return (NULL);
    expanded = expand_string(path, shell->env, shell->last_exit_status);
    if (!expanded)
        return ft_strdup(path); // fallback if expand_string fails
    return expanded;
}



void	print_cd_help(void)
{
	ft_putendl_fd("cd: cd [-L|[-P [-e]] [-@]] [dir]", 1);
	ft_putendl_fd("    Change the shell working directory.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    Change the current directory to DIR.  The default DIR is the value of the", 1);
	ft_putendl_fd("    HOME shell variable. If DIR is \"-\", it is converted to $OLDPWD.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    The variable CDPATH defines the search path for the directory containing", 1);
	ft_putendl_fd("    DIR.  Alternative directory names in CDPATH are separated by a colon (:).", 1);
	ft_putendl_fd("    A null directory name is the same as the current directory.  If DIR begins", 1);
	ft_putendl_fd("    with a slash (/), then CDPATH is not used.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    If the directory is not found, and the shell option `cdable_vars' is set,", 1);
	ft_putendl_fd("    the word is assumed to be  a variable name.  If that variable has a value,", 1);
	ft_putendl_fd("    its value is used for DIR.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    Options:", 1);
	ft_putendl_fd("      -L        force symbolic links to be followed: resolve symbolic", 1);
	ft_putendl_fd("                links in DIR after processing instances of `..'", 1);
	ft_putendl_fd("      -P        use the physical directory structure without following", 1);
	ft_putendl_fd("                symbolic links: resolve symbolic links in DIR before", 1);
	ft_putendl_fd("                processing instances of `..'", 1);
	ft_putendl_fd("      -e        if the -P option is supplied, and the current working", 1);
	ft_putendl_fd("                directory cannot be determined successfully, exit with", 1);
	ft_putendl_fd("                a non-zero status", 1);
	ft_putendl_fd("      -@        on systems that support it, present a file with extended", 1);
	ft_putendl_fd("                attributes as a directory containing the file attributes", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    The default is to follow symbolic links, as if `-L' were specified.", 1);
	ft_putendl_fd("    `..' is processed by removing the immediately previous pathname component", 1);
	ft_putendl_fd("    back to a slash or the beginning of DIR.", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("    Exit Status:", 1);
	ft_putendl_fd("    Returns 0 if the directory is changed, and if $PWD is set successfully when", 1);
	ft_putendl_fd("    -P is used; non-zero otherwise.", 1);
}



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
    else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
    {
        path = get_env_value("OLDPWD", shell->env);
        if (!path)
        {
            ft_putendl_fd("cd: OLDPWD not set", 2);
            return (NULL);
        }
        printf("%s\n", path);
    }
    else if (ft_strncmp(cmd->args[1], "~", 2) == 0)
    {
        path = get_env_value("HOME", shell->env);
        if (!path)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return (NULL);
        }
    }
	else if (ft_strncmp(cmd->args[1], "--help", 7) == 0)
    {
		print_cd_help();
        return (NULL);
    }
    else
        path = expand_path(cmd->args[1], shell);

    return (path);
}


int change_dir_and_update(t_shell *shell, char *path, char *pwd)
{
    char *new_pwd;

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
        return (1);
    path = get_cd_path(cmd, shell);
    if (!path)
    {
        free(pwd);
        return (1);
    }
    return (change_dir_and_update(shell, path, pwd));
}

