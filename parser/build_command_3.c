
#include "parsing.h"


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

static int	append_quoted_word(t_cmd *cmd, t_token *token, int *index)
{
    if (!token->value)
        return (0);
    cmd->args[*index] = strdup(token->value);
    if (!cmd->args[*index])
        return (0);
    (*index)++;
    return (1);
}

static int	append_unquoted_words(t_cmd *cmd, t_token *token, int *index)
{
    char	*start;
    char	*word;
    int		len;

    start = token->value;
    if (!start)
        return (0);
    while (*start)
    {
        while (*start == ' ' || *start == '\t' || *start == '\n')
            start++;
        if (!*start)
            break ;
        len = 0;
        while (start[len] && start[len] != ' ' && start[len] != '\t'
            && start[len] != '\n')
            len++;
        word = ft_substr(start, 0, len);
        if (!word)
            return (0);
        cmd->args[*index] = word;
        (*index)++;
        start += len;
    }
    return (1);
}

int handle_word_token(t_cmd *cmd, t_token *token, int *index)
{
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
