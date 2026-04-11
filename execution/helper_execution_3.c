#include "execution.h"


void	close_extra_fds_for_exec(void)
{
    int		fd;

    fd = 3;
    while (fd < 1024)
    {
        close(fd);
        fd++;
    }
}



void	cleanup_child_state(t_shell *shell)
{
    if (!shell)
        return ;
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
    free_shell(shell);
    rl_clear_history();
}

static char	**build_sh_fallback_args(t_cmd *cmd, char *cmd_path)
{
    int		argc;
    int		i;
    char	**sh_argv;

    argc = 0;
    while (cmd->args && cmd->args[argc])
        argc++;
    sh_argv = ft_calloc(argc + 2, sizeof(char *));
    if (!sh_argv)
        return (NULL);
    sh_argv[0] = "/bin/sh";
    sh_argv[1] = cmd_path;
    i = 1;
    while (i < argc)
    {
        sh_argv[i + 1] = cmd->args[i];
        i++;
    }
    sh_argv[argc + 1] = NULL;
    return (sh_argv);
}





int wait_for_child(pid_t pid)
{
    int status;
    int sig;
    int i;

    i = waitpid(pid, &status, 0);
    while (i == -1 && errno == EINTR)
        i = waitpid(pid, &status, 0);
    if (i == -1)
        return (1);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    if (!WIFSIGNALED(status))
        return (1);
    sig = WTERMSIG(status);
    g_last_signal = sig;
    return (128 + sig);
}




char **prepare_envp(t_shell *shell)
{
    char **envp;

    envp = env_list_to_envp(shell->env);
    return (envp);
}


static void	handle_exec_error(t_cmd *cmd, char *cmd_path, char **envp, t_shell *shell)
{
	int	exec_status;

	ft_putstr_fd("minishell: ", 2);
	perror(cmd->args[0]);
	exec_status = 126;
	if (errno == ENOENT)
		exec_status = 127;
	free(cmd_path);
	free_2D(envp);
	cleanup_child_state(shell);
	_exit(exec_status);
}


static void	try_sh_fallback(t_cmd *cmd, char *cmd_path, char **envp)
{
	char	**sh_argv;

	if (errno == ENOEXEC)
	{
		sh_argv = build_sh_fallback_args(cmd, cmd_path);
		if (sh_argv)
		{
			execve("/bin/sh", sh_argv, envp);
			free(sh_argv);
		}
	}
}


static void	execute_command(t_cmd *cmd, char *cmd_path, char **envp, t_shell *shell)
{
	if (execve(cmd_path, cmd->args, envp) == -1)
	{
		try_sh_fallback(cmd, cmd_path, envp);
		handle_exec_error(cmd, cmd_path, envp, shell);
	}
}


static int	validate_child_command_access(char *cmd_path, t_cmd *cmd)
{
    struct stat	st;

    if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
    {
        print_is_directory(cmd->args[0]);
        return (126);
    }
    if (access(cmd_path, X_OK) != 0)
    {
        print_cmd_errno(cmd->args[0]);
        if (errno == ENOENT)
            return (127);
        return (126);
    }
    return (0);
}


static void	handle_redirection_fail(char **envp, t_shell *shell)
{
	free_2D(envp);
	cleanup_child_state(shell);
	_exit(1);
}


void	execute_child_process(t_cmd *cmd, char **envp, t_shell *shell)
{
    char	*cmd_path;
    int		path_available;
    int		status;

	setup_child_signals();
	if (!apply_redirections(cmd->redirections, shell))
        handle_redirection_fail(envp, shell);
    path_available = is_path_available(shell);
    cmd_path = resolve_path_or_fail(cmd, shell, envp, path_available);
    if (!cmd_path)
    {
        free_2D(envp);
        cleanup_child_state(shell);
        _exit(127);
    }
    status = validate_child_command_access(cmd_path, cmd);
    if (status != 0)
    {
        free(cmd_path);
        free_2D(envp);
        cleanup_child_state(shell);
        _exit(status);
    }
	close_extra_fds_for_exec();
	execute_command(cmd, cmd_path, envp, shell);
}




// void execute_child_process(t_cmd *cmd, char *cmd_path, char **envp , t_shell *shell)
// {
//     int     exec_status;
//     char    **sh_argv;

//     setup_child_signals();
//     if (!apply_redirections(cmd->redirections, shell))
//     {
//         free(cmd_path);
//         free_2D(envp);
//         cleanup_child_state(shell);
//         _exit(1);
//     }
//     close_extra_fds_for_exec();
//     if (execve(cmd_path, cmd->args, envp) == -1)
//     {
//         if (errno == ENOEXEC)
//         {
//             sh_argv = build_sh_fallback_args(cmd, cmd_path);
//             if (sh_argv)
//             {
//                 execve("/bin/sh", sh_argv, envp);
//                 free(sh_argv);
//             }
//         }
//         ft_putstr_fd("minishell: ", 2);
//         perror(cmd->args[0]);
//         exec_status = 126;
//         if (errno == ENOENT)
//             exec_status = 127;
//         free(cmd_path);
//         free_2D(envp);
//         cleanup_child_state(shell);
//         _exit(exec_status);
//     }
// }

