/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:22 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:31:29 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	fill_matches_from_ls(t_wildcard *ctx)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;
	int		ok;

	if (pipe(pipe_fd) < 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (0);
	}
	if (pid == 0)
		exec_ls_child(pipe_fd);
	status = 0;
	close(pipe_fd[1]);
	ok = read_ls_output(pipe_fd[0], ctx);
	close(pipe_fd[0]);
	return (wait_and_check(pid, status, ok));
}

void	exec_ls_child(int pipe_fd[2])
{
	char	*argv[3];

	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	argv[0] = "/bin/ls";
	argv[1] = "-a1";
	argv[2] = NULL;
	execve("/bin/ls", argv, NULL);
	exit(1);
}

int	read_ls_output(int fd, t_wildcard *ctx)
{
	t_wildcard_read_state	state;

	state.bytes = 0;
	state.index = 0;
	state.line_len = 0;
	while (1)
	{
		state.bytes = read(fd, state.buffer, sizeof(state.buffer));
		if (state.bytes <= 0)
			break ;
		state.index = 0;
		if (!consume_chunk(ctx, &state))
			return (0);
	}
	if (state.bytes < 0)
		return (0);
	if (!flush_pending_line(ctx, &state))
		return (0);
	return (1);
}

int	consume_chunk(t_wildcard *ctx, t_wildcard_read_state *state)
{
	while (state->index < state->bytes)
	{
		if (state->buffer[state->index] == '\n')
		{
			state->line[state->line_len] = '\0';
			if (match_pattern(ctx->pattern, state->line)
				&& !append_match(ctx->matches, ctx->count, ctx->cap,
					state->line))
				return (0);
			state->line_len = 0;
		}
		else if (state->line_len < 1023)
			state->line[state->line_len++] = state->buffer[state->index];
		state->index++;
	}
	return (1);
}

int	match_pattern(const char *pattern, const char *name)
{
	if (!pattern || !name)
		return (0);
	if (name[0] == '.' && pattern[0] != '.')
		return (0);
	return (wildcard_match(pattern, name));
}
