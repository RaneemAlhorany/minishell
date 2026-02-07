/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:13:44 by babo-sai          #+#    #+#             */
/*   Updated: 2025/09/01 11:04:04 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char	to_upper_even1(unsigned int i, char c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32); 
    return (c);
}
 
int	main(void)
{
    char *str = "hello world";
    char *new_str = ft_strmapi(str, to_upper_even);

    printf("%s\n", new_str); 

    free(new_str); 
}*/
