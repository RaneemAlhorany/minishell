
#include "builtin.h"

static int	matches_env_key(t_env *node, char *key)
{
    return (ft_strncmp(node->key, key, ft_strlen(key) + 1) == 0);
}

static void	unlink_env_node(t_shell *shell, t_env *prev, t_env *node)
{
    if (prev == NULL)
        shell->env = node->next;
    else
        prev->next = node->next;
    free(node->key);
    if (node->value)
        free(node->value);
    free(node);
}

void remove_env(t_shell *shell, char *key)
{
    t_env *temp;
    t_env *prev;

    if (!shell || !shell->env || !key)
        return;
    temp = shell -> env;
    prev = NULL;
    while (temp)
    {
        if (matches_env_key(temp, key))
        {
            unlink_env_node(shell, prev, temp);
            return ;
        }
        prev = temp;
        temp = temp ->next;
    }
}

char *strip_quotes(char *str)
{
    if (!str)
        return (NULL);
    return (ft_strtrim(str, "\""));
}

void process_unset_args(t_cmd *cmd, t_shell *shell, int i)
{
    char *key;

    while (cmd->args[i])
    {
        key = strip_quotes(cmd->args[i]);
        if (key)
        {
            remove_env(shell, key);
            free(key);
        }
        i++;
    }
}

int handle_unset_option(t_cmd *cmd, int *i)
{
    if (cmd->args[1] && cmd->args[1][0] == '-')
    {
        if (parse_char_flag(cmd->args ,i ,'v'))
            *i = 2;
        else
        {
            ft_putendl_fd("unset:invalid option", 2);
            ft_putendl_fd("unset: usage: unset [-v] [name ...]", 2);
            return (1);
        }
    }
    return (0);
}

int builtin_unset(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd || !shell)
        return (1);
    i = 1;
    if (handle_unset_option(cmd, &i))
        return (1);
    process_unset_args(cmd, shell, i);
    return (0);
}
