/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:10:18 by ralhoura          #+#    #+#             */
/*   Updated: 2025/09/03 14:19:45 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_of_int_variable(int n);

char	*ft_itoa(int n)
{
	int		len;
	char	*value_itoa;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = len_of_int_variable(n);
	value_itoa = malloc(len + 1);
	if (!value_itoa)
		return (NULL);
	if (n == 0)
		value_itoa[0] = '0';
	if (n < 0)
	{
		value_itoa[0] = '-';
		n *= -1;
	}
	value_itoa[len] = '\0';
	while (n != 0)
	{
		value_itoa[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (value_itoa);
}

int	len_of_int_variable(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}
