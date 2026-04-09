#include "execution.h"




void restore_fds(int stdin_copy, int stdout_copy)
{
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
}

 size_t get_total_length(const char *prefix,const char *name,const char *suffix)
{
    return (ft_strlen(prefix)
        + ft_strlen(name)
        + ft_strlen(suffix));
}

 void fallback_print(char *cmd_name)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd_name, 2);
    ft_putendl_fd(": command not found", 2);
}

 char *build_error_line(const char *prefix,const char *name,const char *suffix)
{
    char    *line;
    size_t  len;

    len = get_total_length(prefix, name, suffix);
    line = malloc(len + 1);
    if (!line)
        return (NULL);
    ft_memcpy(line, prefix, ft_strlen(prefix));
    ft_memcpy(line + ft_strlen(prefix), name, ft_strlen(name));
    ft_memcpy(line + ft_strlen(prefix) + ft_strlen(name),
        suffix, ft_strlen(suffix));
    line[len] = '\0';
    return (line);
}



 void print_command_not_found_line(char *cmd_name)
{
    const char  *prefix;
    const char  *suffix;
    char        *line;
    size_t      len;

    prefix = "minishell: ";
    suffix = ": command not found\n";

    line = build_error_line(prefix, cmd_name, suffix);
    if (!line)
        return (fallback_print(cmd_name));

    len = get_total_length(prefix, cmd_name, suffix);
    write(2, line, len);
    free(line);
}


// static void	print_command_not_found_line(char *cmd_name)
// {
//     const char	*prefix;
//     const char	*suffix;
//     char		*line;
//     size_t		prefix_len;
//     size_t		name_len;
//     size_t		suffix_len;

//     prefix = "minishell: ";
//     suffix = ": command not found\n";
//     prefix_len = ft_strlen(prefix);
//     name_len = ft_strlen(cmd_name);
//     suffix_len = ft_strlen(suffix);
//     line = malloc(prefix_len + name_len + suffix_len + 1);
//     if (!line)
//     {
//         ft_putstr_fd("minishell: ", 2);
//         ft_putstr_fd(cmd_name, 2);
//         ft_putendl_fd(": command not found", 2);
//         return ;
//     }
//     ft_memcpy(line, prefix, prefix_len);
//     ft_memcpy(line + prefix_len, cmd_name, name_len);
//     ft_memcpy(line + prefix_len + name_len, suffix, suffix_len);
//     line[prefix_len + name_len + suffix_len] = '\0';
//     write(2, line, prefix_len + name_len + suffix_len);
//     free(line);
// }






