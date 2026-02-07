/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:16:58 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/27 11:35:49 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p = 0;
		p++;
	}
	return ;
}
/*
int	main(int argc, char const *argv[])
{
    char str1[10] = "Helloaaaa";

    ft_bzero(str1 + 3, 4);
    printf("%s\n", str1); 

    return (0);
      int str1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ft_bzero(str1 + 3 , 4);
 printf("%d\n", str1[3]); 

return (0);
}*/