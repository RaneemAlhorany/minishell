#include "execution.h"



 char *init_buffer_herdoc(size_t *cap)
{
    char *buf;

    *cap = 128;
    buf = malloc(*cap);
    return (buf);
}

 int handle_read(ssize_t n, char *buf, size_t len)
{
    if (n == 0 && len == 0)
        return (free(buf), 0);
    if (n < 0)
        return (free(buf), 0);
    return (1);
}

 char *resize_buffer(char *buf, size_t *cap, size_t len)
{
    char *tmp;

    *cap *= 2;
    tmp = malloc(*cap);
    if (!tmp)
        return (free(buf), NULL);
    ft_memcpy(tmp, buf, len);
    free(buf);
    return (tmp);
}

 char *read_loop(char *buf, size_t *len, size_t *cap)
{
    char    c;
    ssize_t n;

    while (1)
    {
        n = read(STDIN_FILENO, &c, 1);
        if (n <= 0 || c == '\n')
            break ;
        if (*len + 1 >= *cap)
        {
            buf = resize_buffer(buf, cap, *len);
            if (!buf)
                return (NULL);
        }
        buf[(*len)++] = c;
    }
    if (!handle_read(n, buf, *len))
        return (NULL);
    return (buf);
}

char *read_heredoc_line(void)
{
    char    *buf;
    size_t  len;
    size_t  cap;

    len = 0;
    buf = init_buffer_herdoc(&cap);
    if (!buf)
        return (NULL);
    buf = read_loop(buf, &len, &cap);
    if (!buf)
        return (NULL);
    buf[len] = '\0';
    return (buf);
}

