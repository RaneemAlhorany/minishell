/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:56:52 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/01 14:21:21 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end >= start && ft_strrchr(set, s1[end]))
		end--;
	trimmed_str = malloc(end - start + 2);
	if (!trimmed_str)
		return (NULL);
	ft_memcpy(trimmed_str, &s1[start], end - start + 1);
	trimmed_str[end - start + 1] = '\0';
	return (trimmed_str);
}
