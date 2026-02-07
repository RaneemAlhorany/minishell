/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:38:33 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/18 12:36:07 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;
	t_list	*new;

	if (lst == NULL || del == NULL)
		return ;
	clear = *lst;
	while (clear != NULL)
	{
		new = clear->next;
		ft_lstdelone(clear, del);
		clear = new;
	}
	*lst = NULL;
}
