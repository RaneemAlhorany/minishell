#include "execution.h"



int handle_command_not_found(char *cmd_name, char *cmd_path, char **envp)
{
    if (cmd_path)
        free(cmd_path);
    free_2D(envp);
    if (cmd_name && *cmd_name)
        print_command_not_found_line(cmd_name);
    else
        ft_putendl_fd("minishell: : command not found", 2);
    return (127);
}


char *resolve_command_path(t_cmd *cmd, t_shell *shell)
{
    char *cmd_path;

    if (ft_strchr(cmd->args[0], '/'))
        cmd_path = ft_strdup(cmd->args[0]);
    else
        cmd_path = find_program_on_path(cmd->args[0], shell);
    return (cmd_path);
}

 int resize_array(char ***arr, int *cap, int count)
{
    char    **new_arr;
    int     i;

    if (*cap == 0)
        *cap = 8;
    else
        *cap *= 2;

    new_arr = malloc(sizeof(char *) * (*cap));
    if (!new_arr)
        return (0);

    i = 0;
    while (i < count)
    {
        new_arr[i] = (*arr)[i];
        i++;
    }
    free(*arr);
    *arr = new_arr;
    return (1);
}

 int add_element(char **arr, int *count, char *name)
{
    arr[*count] = ft_strdup(name);
    if (!arr[*count])
        return (0);
    (*count)++;
    return (1);
}


int append_match(char ***arr, int *count, int *cap, char *name)
{
    if (*count >= *cap)
    {
        if (!resize_array(arr, cap, *count))
            return (0);
    }
    return (add_element(*arr, count, name));
}


// int	append_match(char ***arr, int *count, int *cap, char *name)
// {
//     char	**new_arr;
//     int		i;

//     if (*count >= *cap)
//     {
//         if (*cap == 0)
//             *cap = 8;
//         else
//             *cap *= 2;
//         new_arr = malloc(sizeof(char *) * (*cap));
//         if (!new_arr)
//             return (0);
//         i = 0;
//         while (i < *count)
//         {
//             new_arr[i] = (*arr)[i];
//             i++;
//         }
//         free(*arr);
//         *arr = new_arr;
//     }
//     (*arr)[*count] = ft_strdup(name);
//     if (!(*arr)[*count])
//         return (0);
//     (*count)++;
//     return (1);
// }
