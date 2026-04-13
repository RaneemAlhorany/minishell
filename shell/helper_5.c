#include "shell.h"




void	shell_interactive(t_shell *shell)
{
	char	*line;
	char	*prompt;

	while (shell && shell->is_running)
	{
		clear_last_signal();
		set_interactive_readline_mode(1);
		prompt = build_prompt(shell);
		line = readline(prompt);
		free(prompt);
		handle_sigint(shell);
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		process_line(shell, line);
		free(line);
	}
}


void increment_shlvl(t_shell *shell)
{
    t_env *shlvl_node;
    int    current_level;
    int    next_level;

    if (!shell)
        return ;

    shlvl_node = find_env(shell->env, "SHLVL");
    current_level = get_current_level(shlvl_node);
    next_level = compute_next_level(current_level);

    update_shlvl_value(shell, next_level);
}




void cleanup_execution(t_shell *shell, t_ast *ast, t_token *tokens)
{
    free_ast(ast);
    free_tokens(tokens);
    shell->active_tokens = NULL;
    shell->active_ast = NULL;
}

static t_token	*tokenize_prepared_input(char *line, t_token **tokens_head)
{
    char	*input;
    t_token	*tokens;

    input = prepare_input(line);
    if (!input)
        return (NULL);
    tokens = get_tokens(input);
    free(input);
    if (!tokens)
        return (NULL);
    *tokens_head = tokens;
    return (tokens);
}


t_ast *prepare_execution(t_shell *shell, char *line, t_token **tokens_head)
{
    t_token *tokens;

    if (!shell)
        return (NULL);

    tokens = tokenize_prepared_input(line, tokens_head);
    if (!tokens)
        return (NULL);

    if (!expand_tokens_safe(tokens, shell))
        return (NULL);

    if (!check_syntax(tokens))
        return (NULL);

    return (parse_pipeline(&tokens));
}
