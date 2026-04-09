#include "execution.h"



int	compare_match_names(char *a, char *b)
{
    int				 i;
    unsigned char	ca;
    unsigned char	cb;

    i = 0;
    while (a[i] && b[i])
    {
        ca = (unsigned char)ft_tolower(a[i]);
        cb = (unsigned char)ft_tolower(b[i]);
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


int is_valid_command(t_ast *node)
{
    if (!node || !node->cmd || !node->cmd->args || !node->cmd->args[0])
        return (0);
    return (1);
}
