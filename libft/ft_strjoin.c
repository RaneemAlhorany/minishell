/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:09:31 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/16 14:44:16 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*sub_s;

	if (!s1 || !s2)
		return (NULL);
	len_s2 = ft_strlen(s2);
	len_s1 = ft_strlen(s1);
	sub_s = (char *)malloc((len_s2 + len_s1 + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	sub_s[0] = 0;
	ft_strlcat(sub_s, s1, len_s1 + 1);
	ft_strlcat(sub_s, s2, len_s1 + len_s2 + 1);
	return (sub_s);
}
