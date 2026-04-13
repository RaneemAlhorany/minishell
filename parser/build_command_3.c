
#include "parsing.h"

static int	is_reserved_word(const char *word)
{
	static const char	*reserved[] = {
		"in", "do", "done", "if", "then", "elif", "else", "fi",
		"while", "until", "for", "case", "esac", "select",
		"function", "{", "}", "[[", "]]", "!", NULL
	};
	int	i;

	i = 0;
	while (reserved[i])
	{
		if (ft_strlen(word) == ft_strlen(reserved[i])
			&& ft_strncmp(word, reserved[i], ft_strlen(reserved[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	fill_command_data(t_ast *node, t_token **tokens)
{
	int	has_word;

	has_word = 0;
	if (!process_command_tokens(node, tokens, &has_word))
		return (0);
	if (!has_word && !node->cmd->redirections)
		return (0);
	return (1);
}

int	append_quoted_word(t_cmd *cmd, t_token *token, int *index)
{
    if (!token->value)
        return (0);
    cmd->args[*index] = strdup(token->value);
    if (!cmd->args[*index])
        return (0);
    (*index)++;
    return (1);
}

static char	*next_unquoted_word(char **start)
{
	int		len;
	char	*word;

	while (**start == ' ' || **start == '\t' || **start == '\n')
		(*start)++;
	if (!**start)
		return (NULL);
	len = 0;
	while ((*start)[len] && (*start)[len] != ' '
		&& (*start)[len] != '\t' && (*start)[len] != '\n')
		len++;
	word = ft_substr(*start, 0, len);
	*start += len;
	return (word);
}

int	append_unquoted_words(t_cmd *cmd, t_token *token, int *index)
{
    char	*start;
    char	*word;

    start = token->value;
    if (!start)
    {
        return (0);
    }
	while (*start)
    {
        word = next_unquoted_word(&start);
		if (!word && *start)
			return (0);
		if (!word)
			break ;
		cmd->args[*index] = word;
		(*index)++;
    }
    return (1);
}

int handle_word_token(t_cmd *cmd, t_token *token, int *index)
{
	if (*index == 0 && is_reserved_word(token->value))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putendl_fd("'", 2);
		return (0);
	}
	if (token->quoted)
		return (append_quoted_word(cmd, token, index));
	return (append_unquoted_words(cmd, token, index));
}



int handle_redirection_token(t_cmd *cmd,t_token **tokens, t_redirection **last)
{
    t_redirection *new_redir;

    if (!(*tokens)->next || (*tokens)->next->type != TOKEN_WORD)
        return (0);
    new_redir = create_redirection(*tokens);
    if (!new_redir)
        return (0);

    add_redirection(cmd, new_redir, last);

    *tokens = (*tokens)->next; // skip filename
    return (1);
}
