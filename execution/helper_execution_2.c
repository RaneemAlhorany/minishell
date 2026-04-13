#include "execution.h"


 int	copy_normal_arg(char **new_args, int *j, char *arg)
{
	new_args[*j] = ft_strdup(arg);
	if (!new_args[*j])
		return (0);
	(*j)++;
	return (1);
}


 int	add_matches(char **new_args, int *j, char **matches, int match_count)
{
	int	k;

	k = 0;
	while (k < match_count)
	{
		new_args[*j] = ft_strdup(matches[k]);
		if (!new_args[*j])
			return (0);
		(*j)++;
		k++;
	}
	return (1);
}


 int	handle_wildcard(char **new_args, int *j, char *arg)
{
	char	**matches;
	int		match_count;

	if (!collect_matches(arg, &matches, &match_count))
		return (0);
	if (match_count == 0)
	{
		if (!copy_normal_arg(new_args, j, arg))
			return (free_str_array(matches, match_count), 0);
	}
	else
	{
		if (!add_matches(new_args, j, matches, match_count))
			return (free_str_array(matches, match_count), 0);
	}
	free_str_array(matches, match_count);
	return (1);
}

static int	copy_arg_with_wildcard(char **new_args, int *j, char *arg)
{
	if (!has_wildcard_chars(arg))
		return (copy_normal_arg(new_args, j, arg));
	return (handle_wildcard(new_args, j, arg));
}


 int	process_args(char **args, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (!copy_arg_with_wildcard(new_args, &j, args[i]))
			return (free_partial_args(new_args, j), 0);
		i++;
	}
	new_args[j] = NULL;
	return (1);
}


int	expand_cmd_wildcards(t_cmd *cmd)
{
	int		words;
	char	**new_args;

	if (!cmd || !cmd->args)
		return (1);

	words = count_expanded_words(cmd->args);
	if (words < 0)
		return (0);

	new_args = malloc(sizeof(char *) * (words + 1));
	if (!new_args)
		return (0);

	if (!process_args(cmd->args, new_args))
		return (0);

	free_2D(cmd->args);
	cmd->args = new_args;
	return (1);
}
