/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:44:04 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/01 14:34:34 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int Replaced_value, size_t num)
{
	size_t			index;
	unsigned char	*str;

	index = -1;
	str = (unsigned char *)ptr;
	while (++index < num)
		str[index] = (unsigned char)Replaced_value;
	return (str);
}
