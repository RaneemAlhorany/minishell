#include "shell.h"



 int	handle_prepare(t_shell *shell,t_token *tokens_head, t_ast *ast)
{
	set_active_state(shell, tokens_head, ast);
	if (!ast)
		return (handle_prepare_failure(shell, tokens_head));
	return (-1);
}

 int	handle_heredoc_shell(t_shell *shell,t_ast *ast, t_token *tokens_head)
{
	int	preload_status;

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
	return (-1);
}

 int	execute_phase(t_shell *shell, t_ast *ast)
{
	int	status;

	status = execute_and_update(shell, ast);
	// if (get_last_signal() == SIGINT)
	// {
	// 	status = 130;
	// 	clear_last_signal();
	// }
	shell->last_exit_status = status;
	return (status);
}

int	execute_line(t_shell *shell, char *line)
{
	t_token	*tokens_head;
	t_ast	*ast;
	int		status;

	tokens_head = NULL;
	ast = prepare_execution(shell, line, &tokens_head);

	status = handle_prepare(shell, tokens_head, ast);
	if (status != -1)
		return (status);

	status = handle_heredoc_shell(shell, ast, tokens_head);
	if (status != -1)
		return (status);

	status = execute_phase(shell, ast);
	cleanup_execution(shell, ast, tokens_head);
	return (status);
}

// int execute_line(t_shell *shell, char *line)
// {
//     t_token *tokens_head;
//     t_ast   *ast;
//     int     status;
//     int     preload_status;

//     tokens_head = NULL;
//     ast = prepare_execution(shell, line, &tokens_head);

//     set_active_state(shell, tokens_head, ast);

//     if (!ast)
//         return (handle_prepare_failure(shell, tokens_head));

//     preload_status = preload_heredocs_ast(ast, shell);
//     if (preload_status == -2)
//     {
//         shell->last_exit_status = 130;
//         cleanup_execution(shell, ast, tokens_head);
//         return (130);
//     }
//     if (preload_status != 0)
//     {
//         shell->last_exit_status = 1;
//         cleanup_execution(shell, ast, tokens_head);
//         return (1);
//     }

//     status = execute_and_update(shell, ast);
//         if (get_last_signal() == SIGINT)
//         {
// 		status = 130;
// 		clear_last_signal();
// 	}
//     shell->last_exit_status = status;

//     cleanup_execution(shell, ast, tokens_head);

//     return (status);
// }


