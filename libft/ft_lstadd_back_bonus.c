/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:36:36 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/18 12:37:42 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastnode;

	if (*lst)
	{
		lastnode = ft_lstlast(*lst);
		lastnode->next = new;
	}
	else
	{
		*lst = new;
	}
}
/*int main(void)
{
    t_list *head = ft_lstnew("Node 1");
    t_list *new_node = ft_lstnew("Node 2");

    ft_lstadd_back(&head, new_node);
    printf("First node content: %s\n", (char *)head->content);
    printf("Second node content: %s\n", (char *)head->next->content);

    new_node = ft_lstnew("Node 3");
    ft_lstadd_back(&head, new_node);
    printf("Third node content: %s\n", (char *)head->next->next->content);

    return (0);
}*/