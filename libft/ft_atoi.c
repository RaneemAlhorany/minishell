/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:17:59 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/16 12:19:10 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	i;
	int	pos_nig;

	pos_nig = 1;
	i = 0;
	ret = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == 45 || nptr[i] == 43)
	{
		if (nptr[i] == 45)
			pos_nig = pos_nig * -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		ret = ((ret * 10) + (nptr[i] - 48));
		i++;
	}
	return (ret * pos_nig);
}
