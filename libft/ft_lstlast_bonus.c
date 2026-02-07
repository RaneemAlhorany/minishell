/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:39:29 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/18 12:38:24 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*int main(void)
{
    t_list *head = ft_lstnew("Node 3");
    ft_lstadd_front(&head, ft_lstnew("Node 2"));
    ft_lstadd_front(&head, ft_lstnew("Node 1"));

    t_list *last_node = ft_lstlast(head);
    if (last_node)
        printf("Last node content: %s\n", (char *)last_node->content);
    else
        printf("List is empty.\n");

    return (0);
}*/
