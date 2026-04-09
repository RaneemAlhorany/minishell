#include "execution.h"


 int	consume_chunk(t_wildcard_collect_ctx *ctx, t_wildcard_read_state *state)
{
    while (state->index < state->bytes)
    {
        if (state->buffer[state->index] == '\n')
        {
            if (!append_pending_line(ctx, state))
                return (0);
        }
        else if (state->line_len < 1023)
            state->line[state->line_len++] = state->buffer[state->index];
        state->index++;
    }
    return (1);
}

 int	flush_pending_line(t_wildcard_collect_ctx *ctx,t_wildcard_read_state *state)
{
    if (state->line_len == 0)
        return (1);
    return (append_pending_line(ctx, state));
}

int	read_ls_output(int fd, t_wildcard_collect_ctx *ctx)
{
    t_wildcard_read_state	state;

    init_read_state(&state);
    while (read_next_chunk(fd, &state) && state.bytes > 0)
    {
        if (!consume_chunk(ctx, &state))
            return (0);
    }
    if (state.bytes < 0)
        return (0);
    if (!flush_pending_line(ctx, &state))
        return (0);
    return (1);
}

 int	create_process(int pipe_fd[2], pid_t *pid)
{
    if (pipe(pipe_fd) < 0)
        return (0);
    *pid = fork();
    if (*pid < 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return (0);
    }
    return (1);
}