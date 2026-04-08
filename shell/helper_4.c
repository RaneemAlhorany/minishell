#include "shell.h"




t_ast *prepare_execution(t_shell *shell, char *line, t_token **tokens_head)
{
    char    *input;
    t_token *tokens;

    if (!shell)
        return (NULL);

    input = prepare_input(line);
    if (!input)
        return (NULL);

    tokens = get_tokens(input);
    free(input);
    if (!tokens)
        return (NULL);

    *tokens_head = tokens;

    if (!expand_tokens_safe(tokens, shell))
        return (NULL);

    if (!check_syntax(tokens))
        return (NULL);

    return (parse_pipeline(&tokens));
}




void cleanup_execution(t_shell *shell, t_ast *ast, t_token *tokens)
{
    free_ast(ast);
    free_tokens(tokens);
    shell->active_tokens = NULL;
    shell->active_ast = NULL;
}


int execute_line(t_shell *shell, char *line)
{
    t_token *tokens_head;
    t_ast   *ast;
    int     status;
    int     preload_status;

    tokens_head = NULL;
    ast = prepare_execution(shell, line, &tokens_head);

    set_active_state(shell, tokens_head, ast);

    if (!ast)
        return (handle_prepare_failure(shell, tokens_head));

    preload_status = preload_heredocs_ast(ast, shell);
    if (preload_status == -2)
    {
        shell->last_exit_status = 130;
        cleanup_execution(shell, ast, tokens_head);
        return (130);
    }
    if (preload_status != 0)
    {
        shell->last_exit_status = 1;
        cleanup_execution(shell, ast, tokens_head);
        return (1);
    }

    status = execute_and_update(shell, ast);
        if (get_last_signal() == SIGINT)
        {
		status = 130;
		clear_last_signal();
	}
    shell->last_exit_status = status;

    cleanup_execution(shell, ast, tokens_head);

    return (status);
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


