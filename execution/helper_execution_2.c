#include "execution.h"
#include <glob.h>



int is_valid_external_cmd(t_cmd *cmd, t_shell *shell)
{
    if (!cmd || !cmd->args || !cmd->args[0] || !shell)
        return (0);
    return (1);
}

static int	has_wildcard_chars(const char *arg)
{
    if (!arg)
        return (0);
    while (*arg)
    {
        if (*arg == '*' || *arg == '?' || *arg == '[')
            return (1);
        arg++;
    }
    return (0);
}

static int	count_expanded_words(char **args)
{
    int		count;
    int		i;
    glob_t	g;

    count = 0;
    i = 0;
    while (args && args[i])
    {
        if (!has_wildcard_chars(args[i]))
            count++;
        else
        {
            if (glob(args[i], GLOB_NOCHECK, NULL, &g) != 0)
                return (-1);
            count += (int)g.gl_pathc;
            globfree(&g);
        }
        i++;
    }
    return (count);
}

static void	free_partial_args(char **args, int used)
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
    glob_t	g;
    char	**new_args;

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
            if (glob(cmd->args[i], GLOB_NOCHECK, NULL, &g) != 0)
                return (free_partial_args(new_args, j), 0);
            words = 0;
            while (words < (int)g.gl_pathc)
            {
                new_args[j] = ft_strdup(g.gl_pathv[words]);
                if (!new_args[j])
                {
                    globfree(&g);
                    return (free_partial_args(new_args, j), 0);
                }
                j++;
                words++;
            }
            globfree(&g);
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


