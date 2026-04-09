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
    char    **matches;
    int     count;

    if (!collect_matches(pattern, &matches, &count))
        return (-1);
    free_str_array(matches, count);
    return (count);
}


