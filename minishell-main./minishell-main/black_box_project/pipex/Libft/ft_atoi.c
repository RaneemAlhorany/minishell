/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:24:01 by ralhoura          #+#    #+#             */
/*   Updated: 2025/08/30 13:50:51 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	value;
	int	count;
	int	is_mins;

	count = 0;
	value = 0;
	is_mins = 1;
	while ((nptr[count] > 8 && nptr[count] < 14) || nptr[count] == ' ')
		count++;
	if (nptr[count] == '-' || nptr[count] == '+')
	{
		if (nptr[count] == '-')
			is_mins = -1;
		count++;
	}
	while (ft_isdigit(nptr[count]))
	{
		value = value * 10 + (nptr[count] - '0');
		count++;
	}
	return (value * is_mins);
}
