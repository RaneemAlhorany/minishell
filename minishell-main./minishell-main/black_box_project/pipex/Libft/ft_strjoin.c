/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:36:33 by ralhoura          #+#    #+#             */
/*   Updated: 2025/08/30 13:46:13 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	strjoin = malloc(len_s1 + len_s2 + 1);
	if (!strjoin)
		return (NULL);
	ft_memcpy(strjoin, s1, len_s1);
	ft_memcpy(strjoin + len_s1, s2, len_s2);
	strjoin[len_s1 + len_s2] = '\0';
	return (strjoin);
}
