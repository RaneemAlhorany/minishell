/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:24:14 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/16 12:15:33 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *alltext, const char *need, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*need == '\0')
		return ((char *)(alltext));
	while (alltext[i] != '\0' && i < len)
	{
		j = 0;
		while (need[j] != '\0' && alltext[i + j] == need[j] && (i + j) < len)
		{
			j++;
		}
		if (need[j] == '\0')
			return ((char *)(alltext + i));
		i++;
	}
	return (NULL);
}
//j=1??