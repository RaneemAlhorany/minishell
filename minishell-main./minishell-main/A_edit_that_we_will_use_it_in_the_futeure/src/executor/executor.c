#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

void	set_redirections(t_pipex *px, t_cmd *cmd, int i, int cmd_count)
{
	if (i == 0 && cmd->infile)
		px->infile = cmd->infile;
	if (i == cmd_count - 1 && cmd->outfile)
		px->outfile = cmd->outfile;
}

void	open_child_files(t_pipex *px, int i, int cmd_count, t_cmd *cmd)
{
	int	flags;

	if (i == 0 && px->infile)
		px->infile_fd = open(px->infile, O_RDONLY);

	if (i == cmd_count - 1 && px->outfile)
	{
		flags = O_CREAT | O_WRONLY;

		if (cmd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;

		px->outfile_fd = open(px->outfile, flags, 0644);
	}
}

void	setup_child_fds(t_pipex *px, int i, int cmd_count)
{
	if (i == 0)
	{
		if (px->infile_fd != -1
			&& dup2(px->infile_fd, STDIN_FILENO) == -1)
			child_error_exit(px, NULL);
	}
	else if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
		child_error_exit(px, NULL);
	if (i == cmd_count - 1)
	{
		if (px->outfile_fd != -1
			&& dup2(px->outfile_fd, STDOUT_FILENO) == -1)
			child_error_exit(px, NULL);
	}
	else if (dup2(px->pipes[i][1], STDOUT_FILENO) == -1)
		child_error_exit(px, NULL);
}

void	exec_child(t_pipex *px, t_cmd *cmd)
{
	char	*cmd_path;

	close_pipes(px);
	close_files(px);
	cmd_path = find_cmd_path(cmd->cmd, px->envp);
	if (!cmd_path)
	{
		perror(cmd->cmd);
		exit(127);
	}
	execve(cmd_path, cmd->args, px->envp);
	perror(cmd->cmd);
	exit(127);
}

void	execute_cmds(t_pipex *px, t_cmd *cmds, int cmd_count)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmds;
	while (i < cmd_count && cur)
	{
		set_redirections(px, cur, i, cmd_count);
		px->pids[i] = safe_fork(px);
		if (px->pids[i] == 0)
		{
			open_child_files(px, i, cmd_count, cur);
			setup_child_fds(px, i, cmd_count);
			exec_child(px, cur);
		}
		cur = cur->next;
		i++;
	}
}

void	init_executor(t_pipex *px, char **envp)
{
	ft_memset(px, 0, sizeof(t_pipex));
	px->envp = envp;
	px->infile_fd = -1;
	px->outfile_fd = -1;
}

int	executor(t_cmd *cmds, char **envp)
{
	t_pipex	px;
	int		cmd_count;

	init_executor(&px, envp);
	cmd_count = count_cmds(cmds);
	if (cmd_count == 0)
		return (0);
	px.cmd_count = cmd_count;
	if (cmd_count > 1)
		create_pipes(&px);
	px.pids = malloc(sizeof(pid_t) * cmd_count);
	if (!px.pids)
		return (1);
	execute_cmds(&px, cmds, cmd_count);
	close_pipes(&px);
	close_files(&px);
	wait_for_all_children(&px);
	free_pipes_memory(&px);
	free(px.pids);
	return (px.last_exit);
}
