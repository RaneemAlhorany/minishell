/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:10:18 by ralhoura          #+#    #+#             */
/*   Updated: 2026/03/22 18:25:41 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	len_of_int_variable(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	fill_number(char *str, int n, int len)
{
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
}

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
	fill_number(value_itoa, n, len);
	return (value_itoa);
}
