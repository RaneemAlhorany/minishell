/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:32:39 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/01 14:26:35 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == (char)c)
			return ((char *)(s + count));
		count++;
	}
	if (s[count] == (char)c)
		return ((char *)(s + count));
	return (NULL);
}
