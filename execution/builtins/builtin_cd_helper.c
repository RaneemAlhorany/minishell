
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


char	*get_home_path(t_shell *shell)
{
	char	*path;

	path = get_env_value("HOME", shell->env);
	if (!path)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}

char	*get_oldpwd_path(t_shell *shell)
{
	char	*path;

	path = get_env_value("OLDPWD", shell->env);
	if (!path)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (NULL);
	}
	printf("%s\n", path);
	return (path);
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


