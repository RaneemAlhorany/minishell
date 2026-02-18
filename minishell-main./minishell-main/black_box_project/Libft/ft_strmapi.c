/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:42:16 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/01 18:04:35 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*new_str;

	if (!s || !f)
		return (NULL);
	index = 0;
	new_str = ft_strdup(s);
	if (!new_str)
		return (NULL);
	while (new_str[index] != '\0')
	{
		new_str[index] = f(index, new_str[index]);
		index++;
	}
	return (new_str);
}
