#include "execution.h"


 int	append_if_match(const char *line, t_wildcard_collect_ctx *ctx)
{
    if (!line || !*line)
        return (1);
    if (match_pattern(ctx->pattern, line)
        && !append_match(ctx->matches, ctx->count, ctx->cap, (char *)line))
        return (0);
    return (1);
}

 void	init_read_state(t_wildcard_read_state *state)
{
    state->bytes = 0;
    state->index = 0;
    state->line_len = 0;
}

 int	append_pending_line(t_wildcard_collect_ctx *ctx,t_wildcard_read_state *state)
{
    state->line[state->line_len] = '\0';
    if (!append_if_match(state->line, ctx))
        return (0);
    state->line_len = 0;
    return (1);
}

 int	read_next_chunk(int fd, t_wildcard_read_state *state)
{
    state->bytes = read(fd, state->buffer, sizeof(state->buffer));
    state->index = 0;
    return (state->bytes >= 0);
}


