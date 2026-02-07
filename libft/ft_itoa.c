/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:31:27 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/16 11:31:44 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, int n, int len)
{
	unsigned int	num;
	int				start_index;
	int				i;

	start_index = 0;
	i = len - 1;
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
		start_index = 1;
	}
	else
		num = n;
	str[len] = '\0';
	while (i >= start_index)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = get_len(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	fill_str(str, n, len);
	return (str);
}

/*int main(void)
{
	int numbers[] = {1, 123, -456, -2147483648, 2147483647};
	int i;
	char *s;

	for (i = 0; i < 5; i++)
	{
		s = ft_itoa(numbers[i]);
		if (s)
		{
			printf("%d -> %s\n", numbers[i], s);
			free(s);
		}
	}
	return (0);
}*/