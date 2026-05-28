/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:59 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:23:44 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	buffer_init(t_buffer *buf)
{
	buf->capacity = 64;
	buf->len = 0;
	buf->data = malloc(buf->capacity);
	if (!buf->data)
		return (0);
	buf->data[0] = '\0';
	return (1);
}

int	buffer_append_str(t_buffer *buf, char *str)
{
	size_t	i;

	i = ft_strlen(str);
	if (!buffer_grow(buf, i))
		return (0);
	memcpy(buf->data + buf->len, str, i);
	buf->len += i;
	buf->data[buf->len] = '\0';
	return (1);
}

int	buffer_grow(t_buffer *buf, size_t needed)
{
	char	*new_data;
	size_t	new_capacity;

	if (buf->len + needed + 1 < buf->capacity)
		return (1);
	new_capacity = buf->capacity * 2;
	while (new_capacity <= buf->len + needed + 1)
		new_capacity *= 2;
	new_data = malloc(new_capacity);
	if (!new_data)
		return (0);
	ft_memcpy(new_data, buf->data, buf->len);
	free(buf->data);
	buf->data = new_data;
	buf->capacity = new_capacity;
	return (1);
}

int	buffer_append_char(t_buffer *buf, char c)
{
	if (!buffer_grow(buf, 1))
		return (0);
	buf->data[buf->len++] = c;
	buf->data[buf->len] = '\0';
	return (1);
}
