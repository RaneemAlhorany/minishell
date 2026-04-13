
#include "shell.h"



int	is_str_numeric(const char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}



void	free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->prompt_prefix)
		free(shell->prompt_prefix);
	if (shell->env)
		free_env_list(shell->env);
	free(shell);
}



void free_2D(char **dirs)
{
    int i;

    if (!dirs)
        return;
    i = 0;
    while (dirs[i])
        free(dirs[i++]);
    free(dirs);
}

char	*get_last_arg_from_cmd(t_cmd *cmd)
{
	int		i;
	char	*last;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	i = 0;
	last = cmd->args[0];
	while (cmd->args[i])
	{
		last = cmd->args[i];
		i++;
	}
	return (last);
}



char	*get_last_arg_from_ast(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->type == NODE_COMMAND)
		return (get_last_arg_from_cmd(ast->cmd));
	if (ast->type == NODE_PIPE || ast->type == NODE_AND || ast->type == NODE_OR)
		return (get_last_arg_from_ast(ast->pipe.right));
	if (ast->type == NODE_GROUP)
		return (get_last_arg_from_ast(ast->pipe.left));
	return (NULL);
}
