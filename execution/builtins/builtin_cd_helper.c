
#include "builtin.h"


void	print_cd_help_part_1()
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
    print_cd_help_part_2();
}

void	print_cd_help_part_2()
{
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



char	*get_oldpwd_path(t_shell *shell)
{
	char	*path;

	path = get_env_value("OLDPWD", shell->env);
	if (!path || path[0] == '\0') // here add check for empty string as well, because some shells treat empty OLDPWD as unset
	{
		free(path);
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}

	ft_putendl_fd(path , 1);
	return (path);
}


char	*get_home_path(t_shell *shell)
{
	char	*path;

	path = get_env_value("HOME", shell->env);
	if (!path || path[0] == '\0') // here add check for empty string as well, because some shells treat empty HOME as unset
	{
		free(path);
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}


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



char    *get_parent_path(char *pwd)
{
    int     i;
    char    *parent;

    if (!pwd || pwd[0] == '\0')
        return (NULL);
    i = ft_strlen(pwd) - 1;
    while (i > 0 && pwd[i] == '/')
        i--;
    while (i > 0 && pwd[i] != '/')
        i--;
    if (i == 0)
        return (ft_strdup("/"));
    parent = ft_substr(pwd, 0, i);
    return (parent);
}

