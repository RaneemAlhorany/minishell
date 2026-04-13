
#include "execution.h"

void	setup_pipeline_wrapper_signals(void)
{
    t_sigaction	sa_int;
    t_sigaction	sa_quit;

    sa_int.sa_handler = SIG_IGN;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}


int is_valid_pipe_node(t_ast *node)
{
    if (!node || node->type != NODE_PIPE
        || !node->pipe.left || !node->pipe.right)
        return (0);
    return (1);
}

void execute_left_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    int status;

    setup_pipeline_wrapper_signals();
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    status = execute_ast(node->pipe.left, shell);
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
    _exit(status);
}



void execute_right_child(t_ast *node, t_shell *shell, int pipe_fd[2])
{
    int status;

    setup_pipeline_wrapper_signals();
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    status = execute_ast(node->pipe.right, shell);
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
    _exit(status);
}


int	wait_loop(pid_t left_pid, pid_t right_pid, int *right_status)
{
	int		status;
	int		reaped;
	pid_t	waited;

	reaped = 0;
	while (reaped < 2)
	{
		waited = waitpid(-1, &status, 0);
		if (waited == -1)
		{
			if (errno == EINTR)
				continue ;
			if (errno == ECHILD)
				break ;
			return (1);
		}
		if (waited == left_pid || waited == right_pid)
			reaped++;
		if (waited == right_pid)
			*right_status = status;
	}
	return (0);
}


int	wait_for_pipe(pid_t left_pid, pid_t right_pid)
{
	int	right_status;

	right_status = 0;
	if (wait_loop(left_pid, right_pid, &right_status))
		return (1);
    if (WIFEXITED(right_status))
	{
		if (WEXITSTATUS(right_status) == 128 + SIGQUIT)
			g_last_signal = SIGQUIT;
		return (WEXITSTATUS(right_status));
	}
	if (WIFSIGNALED(right_status))
	{
		g_last_signal = WTERMSIG(right_status);
		return (128 + g_last_signal);
	}
	return (1);
}
