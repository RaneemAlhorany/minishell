/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_helper_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:17:30 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:34:36 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	setup_child_stdin(int *tty_fd, int fd[2], char *limiter, t_shell *shell)
{
	*tty_fd = -1;
	if (isatty(STDIN_FILENO))
		*tty_fd = open("/dev/tty", O_RDONLY);
	if (*tty_fd >= 0)
	{
		if (dup2(*tty_fd, STDIN_FILENO) < 0)
		{
			close(*tty_fd);
			close(fd[0]);
			close(fd[1]);
			free(limiter);
			free_parts(shell);
			free_shell(shell);
			exit(1);
		}
		close(*tty_fd);
	}
}

int	heredoc_loop(int write_fd, char *limiter, t_shell *shell, int quoted)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = read_heredoc_line();
		if (!line)
		{
			if (handle_heredoc_eof(limiter))
				return (1);
			break ;
		}
		if (ft_strlen(line) == ft_strlen(limiter) && ft_strncmp(line, limiter,
				ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, shell, write_fd, quoted);
		free(line);
	}
	return (0);
}

char	*read_heredoc_line(void)
{
	char	*buf;
	size_t	len;
	size_t	cap;

	len = 0;
	cap = 128;
	buf = malloc(cap);
	if (!buf)
		return (NULL);
	buf = read_loop(buf, &len, &cap);
	if (!buf)
		return (NULL);
	buf[len] = '\0';
	return (buf);
}

char	*read_loop(char *buf, size_t *len, size_t *cap)
{
	char	c;
	ssize_t	n;

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
	if ((n == 0 && *len == 0) || n < 0)
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*resize_buffer(char *buf, size_t *cap, size_t len)
{
	char	*tmp;

	*cap *= 2;
	tmp = malloc(*cap);
	if (!tmp)
	{
		free(buf);
		return (NULL);
	}
	ft_memcpy(tmp, buf, len);
	free(buf);
	return (tmp);
}
