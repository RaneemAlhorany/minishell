/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:39:05 by ralhoura          #+#    #+#             */
/*   Updated: 2025/08/18 21:11:02 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length_src;
	size_t	count;

	length_src = ft_strlen(src);
	count = 0;
	if (size == 0)
		return (length_src);
	while (src[count] && count < size - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (length_src);
}
