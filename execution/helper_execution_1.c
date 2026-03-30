#include "execution.h"

static int	is_executable_non_directory(char *path)
{
    struct stat	st;

    if (!path)
        return (0);
    if (access(path, X_OK) != 0)
        return (0);
    if (stat(path, &st) != 0)
        return (0);
    if (S_ISDIR(st.st_mode))
        return (0);
    return (1);
}


int is_valid_external_cmd(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);
    return (1);
}



char *find_program_on_path(char *name, t_shell *shell)
{
    char    **dirs;
    char    *result;

    dirs = get_path_dirs(shell);
    if (!dirs)
        return (NULL);
    result = search_in_dirs(dirs, name);
    free_2D(dirs);
    return (result);
}


char **get_path_dirs(t_shell *shell)
{
    char *path;
    char **dirs;

    path = get_env_value("PATH", shell->env);
    if (!path || !*path)
    {
        free(path);
        return (NULL);
    }
    dirs = ft_split(path, ':');
    free(path);
    return (dirs);
}


char *search_in_dirs(char **dirs, char *name)
{
    char    *candidate;
    int     i;

    i = 0;
    while (dirs[i])
    {
        candidate = join_path(dirs[i], name);
        if (is_executable_non_directory(candidate))
            return (candidate);
        free(candidate);
        i++;
    }
    return (NULL);
}

char *join_path(const char *dir, const char *cmd)
{
    char *tmp;
    char *full;

    if (!dir || !cmd)
        return (NULL);
    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return (NULL);
    full = ft_strjoin(tmp, cmd);
    free(tmp);
    return (full);
}


