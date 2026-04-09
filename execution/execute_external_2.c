
#include "execution.h"


void	print_cmd_errno(const char *cmd_name)
{
    ft_putstr_fd("minishell: ", 2);
    perror(cmd_name);
}

void	print_is_directory(const char *cmd_name)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd((char *)cmd_name, 2);
    ft_putendl_fd(": Is a directory", 2);
}



int is_path_available(t_shell *shell)
{
    char *path_value;
    int  available;

    path_value = get_env_value("PATH", shell->env);
    available = (path_value && *path_value);
    free(path_value);
    return (available);
}


char *resolve_path_or_fail(t_cmd *cmd, t_shell *shell,char **envp, int path_available)
{
    char *cmd_path;

    cmd_path = resolve_command_path(cmd, shell);
    if (!cmd_path)
    {
        if (!ft_strchr(cmd->args[0], '/') && !path_available)
        {
            errno = ENOENT;
            print_cmd_errno(cmd->args[0]);
            free_2D(envp);
            return (NULL);
        }
        handle_command_not_found(cmd->args[0], cmd_path, envp);
        return (NULL);
    }
    return (cmd_path);
}


int validate_command_access(char *cmd_path, t_cmd *cmd, char **envp)
{
    struct stat st;

    if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        print_is_directory(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);
        return (126);
    }
    if (access(cmd_path, X_OK) != 0)
    {
        print_cmd_errno(cmd->args[0]);
        free(cmd_path);
        free_2D(envp);

        if (errno == ENOENT)
            return (127);
        return (126);
    }
    return (0);
}
