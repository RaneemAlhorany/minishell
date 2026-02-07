/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:40:40 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/18 12:39:25 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*int main (void)
{
    t_list *node;

    node = ft_lstnew("Hello, World!");
    if (node)
    {
        printf("Node content: %s\n", (char *)node->content);
        free(node);
    }
    else
    {
        printf("Memory allocation failed\n");
    }
    return (0);
}*/
