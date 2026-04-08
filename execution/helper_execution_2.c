#include "execution.h"



int is_valid_external_cmd(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);
    return (1);
}

int	has_wildcard_chars(char *arg)
{
    if (!arg)
        return (0);
    while (*arg)
    {
        if (*arg == '*')
            return (1);
        arg++;
    }
    return (0);
}

int	wildcard_match(const char *pattern, const char *name)
{
    const char	*star;
    const char	*match;

    star = NULL;
    match = NULL;
    while (*name)
    {
        if (*pattern == '*')
        {
            star = pattern;
            match = name;
            pattern++;
        }
        else if (*pattern == *name)
        {
            pattern++;
            name++;
        }
        else if (star)
        {
            pattern = star + 1;
            match++;
            name = match;
        }
        else
            return (0);
    }
    while (*pattern == '*')
        pattern++;
    return (*pattern == '\0');
}

int	match_pattern(const char *pattern, const char *name)
{
    if (!pattern || !name)
        return (0);
    if ((name[0] == '.' && name[1] == '\0')
        || (name[0] == '.' && name[1] == '.' && name[2] == '\0'))
        return (0);
    if (name[0] == '.' && pattern[0] != '.')
        return (0);
    return (wildcard_match(pattern, name));
}

void	free_str_array(char **arr, int count)
{
    int	i;

    if (!arr)
        return ;
    i = 0;
    while (i < count)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int	count_matches_in_cwd(char *pattern)
{
    DIR			*dir;
    struct dirent	*entry;
    int			count;

    dir = opendir(".");
    if (!dir)
        return (-1);
    count = 0;
    entry = readdir(dir);
    while (entry)
    {
        if (match_pattern(pattern, entry->d_name))
            count++;
        entry = readdir(dir);
    }
    closedir(dir);
    return (count);
}

int	append_match(char ***arr, int *count, int *cap, char *name)
{
    char	**new_arr;
    int		i;

    if (*count >= *cap)
    {
        if (*cap == 0)
            *cap = 8;
        else
            *cap *= 2;
        new_arr = malloc(sizeof(char *) * (*cap));
        if (!new_arr)
            return (0);
        i = 0;
        while (i < *count)
        {
            new_arr[i] = (*arr)[i];
            i++;
        }
        free(*arr);
        *arr = new_arr;
    }
    (*arr)[*count] = ft_strdup(name);
    if (!(*arr)[*count])
        return (0);
    (*count)++;
    return (1);
}

char	to_lower_ascii(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c + 32);
    return (c);
}

int	compare_match_names(char *a, char *b)
{
    int				 i;
    unsigned char	ca;
    unsigned char	cb;

    i = 0;
    while (a[i] && b[i])
    {
        ca = (unsigned char)to_lower_ascii(a[i]);
        cb = (unsigned char)to_lower_ascii(b[i]);
        if (ca != cb)
            return ((int)ca - (int)cb);
        i++;
    }
    return ((unsigned char)a[i] - (unsigned char)b[i]);
}

void	sort_matches(char **matches, int count)
{
    int		i;
    int		j;
    char	*tmp;
    int		cmp;

    i = 1;
    while (i < count)
    {
        tmp = matches[i];
        j = i - 1;
        while (j >= 0)
        {
            cmp = compare_match_names(matches[j], tmp);
            if (cmp <= 0)
                break ;
            matches[j + 1] = matches[j];
            j--;
        }
        matches[j + 1] = tmp;
        i++;
    }
}

int	collect_matches(const char *pattern, char ***matches, int *count)
{
    DIR			*dir;
    struct dirent	*entry;
    int			cap;

    *matches = NULL;
    *count = 0;
    cap = 0;
    dir = opendir(".");
    if (!dir)
        return (0);
    entry = readdir(dir);
    while (entry)
    {
        if (match_pattern(pattern, entry->d_name)
            && !append_match(matches, count, &cap, entry->d_name))
        {
            closedir(dir);
            free_str_array(*matches, *count);
            *matches = NULL;
            *count = 0;
            return (0);
        }
        entry = readdir(dir);
    }
    closedir(dir);
    if (*count > 1)
        sort_matches(*matches, *count);
    return (1);
}

int	count_expanded_words(char **args)
{
    int		count;
    int		i;
    int		matches;

    count = 0;
    i = 0;
    while (args && args[i])
    {
        if (!has_wildcard_chars(args[i]))
            count++;
        else
        {
            matches = count_matches_in_cwd(args[i]);
            if (matches < 0)
                return (-1);
            if (matches == 0)
                count++;
            else
                count += matches;
        }
        i++;
    }
    return (count);
}

void	free_partial_args(char **args, int used)
{
    int	j;

    j = 0;
    while (j < used)
    {
        free(args[j]);
        j++;
    }
    free(args);
}

int	expand_cmd_wildcards(t_cmd *cmd)
{
    int		words;
    int		i;
    int		j;
    char	**new_args;
    char	**matches;
    int		k;
    int		match_count;

    if (!cmd || !cmd->args)
        return (1);
    words = count_expanded_words(cmd->args);
    if (words < 0)
        return (0);
    new_args = malloc(sizeof(char *) * (words + 1));
    if (!new_args)
        return (0);
    i = 0;
    j = 0;
    while (cmd->args[i])
    {
        if (!has_wildcard_chars(cmd->args[i]))
            new_args[j++] = ft_strdup(cmd->args[i]);
        else
        {
            if (!collect_matches(cmd->args[i], &matches, &match_count))
                return (free_partial_args(new_args, j), 0);
            if (match_count == 0)
            {
                new_args[j] = ft_strdup(cmd->args[i]);
                if (!new_args[j])
                    return (free_partial_args(new_args, j), 0);
                j++;
            }
            else
            {
                k = 0;
                while (k < match_count)
                {
                    new_args[j] = ft_strdup(matches[k]);
                    if (!new_args[j])
                    {
                        free_str_array(matches, match_count);
                        return (free_partial_args(new_args, j), 0);
                    }
                    j++;
                    k++;
                }
            }
            free_str_array(matches, match_count);
        }
        if (j > 0 && !new_args[j - 1])
            return (free_partial_args(new_args, j), 0);
        i++;
    }
    new_args[j] = NULL;
    free_2D(cmd->args);
    cmd->args = new_args;
    return (1);
}

int is_valid_command(t_ast *node)
{
    if (!node || !node->cmd || !node->cmd->args || !node->cmd->args[0])
        return (0);
    return (1);
}


void restore_fds(int stdin_copy, int stdout_copy)
{
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
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




int handle_command_not_found(char *cmd_name, char *cmd_path, char **envp)
{
    if (cmd_path)
        free(cmd_path);
    free_2D(envp);
    if (cmd_name && *cmd_name)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd_name, 2);
        ft_putendl_fd(": command not found", 2);
    }
    else
        ft_putendl_fd("minishell: : command not found", 2);
    return (127);
}


