/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:09:48 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/01 14:35:51 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dupstr;

	len = ft_strlen(s);
	dupstr = malloc(len + 1);
	if (!dupstr)
		return (NULL);
	ft_memmove(dupstr, s, len);
	dupstr[len] = '\0';
	return (dupstr);
}
