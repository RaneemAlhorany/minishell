/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:44:00 by ralhoura          #+#    #+#             */
/*   Updated: 2025/08/19 18:28:22 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				count;
	const unsigned char	*src;

	count = 0;
	src = s;
	while (n--)
	{
		if (src[count] == (unsigned char)c)
			return ((void *)&src[count]);
		count++;
	}
	return (NULL);
}
