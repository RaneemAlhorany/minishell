#include "execution.h"

static int	execute_right_branch(t_ast *node, t_shell *shell)
{
	int	status;

	status = execute_ast(node->pipe.right, shell);
	if (shell)
		shell->last_exit_status = status;
	return (status);
}

int	execute_logical_node(t_ast *node, t_shell *shell)
{
	int	status;

	status = execute_ast(node->pipe.left, shell);
	if (shell)
		shell->last_exit_status = status;
	if (!shell || !shell->is_running)
		return (status);
	if (node->type == NODE_AND && status == 0)
		return (execute_right_branch(node, shell));
	if (node->type == NODE_OR && status != 0)
		return (execute_right_branch(node, shell));
	return (status);
}


void	cleanup_child(t_shell *shell, t_ast *node)
{
	if (shell->active_tokens)
	{
		free_tokens(shell->active_tokens);
		shell->active_tokens = NULL;
	}
	if (shell->active_ast)
	{
		free_ast(shell->active_ast);
		shell->active_ast = NULL;
	}
	else
		free_ast(node);
	free_shell(shell);
	rl_clear_history();
}

int	execute_child(t_ast *node, t_shell *shell)
{
	int	status;

	setup_child_signals();
	status = execute_ast(node->pipe.left, shell);
	cleanup_child(shell, node);
	_exit(status);
	return (status);
}

int	execute_group_node(t_ast *node, t_shell *shell)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execute_child(node, shell);

	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		g_last_signal = WTERMSIG(status);
		return (128 + g_last_signal);
	}
	return (1);
}


int execute_ast(t_ast *node , t_shell *shell)
{
    if (!node)
        return (0);

    if (node->type == NODE_COMMAND)
        return (execute_command_node(node, shell));
	else if (node->type == NODE_PIPE)
        return (execute_pipe_node(node, shell));
	else if (node->type == NODE_AND || node->type == NODE_OR)
        return (execute_logical_node(node, shell));
	else if (node->type == NODE_GROUP)
		return (execute_group_node(node, shell));
    return (0);
}

