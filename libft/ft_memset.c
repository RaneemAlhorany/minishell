/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:15:53 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/27 12:16:44 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (s);
}
/*
int	main(int argc, char const *argv[])
{
    char str1[10] = "Helloaaaa";

    ft_memset(str1 + 3, 'u', 4);
    printf("%s\n", str1); 

    return (0);
      int str1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  ft_memset(str1 + 3, 99 , 4);
 printf("%d\n", str1[3]); 

return (0);
}*/
