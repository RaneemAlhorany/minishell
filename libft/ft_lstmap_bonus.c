/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bouns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:58:04 by babo-sai          #+#    #+#             */
/*   Updated: 2025/09/01 11:42:13 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_head;
	t_list	*new;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	n_head = NULL;
	while (lst)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new)
		{
			del(content);
			ft_lstclear(&n_head, del);
			return (NULL);
		}
		ft_lstadd_back(&n_head, new);
		lst = lst->next;
	}
	return (n_head);
}
