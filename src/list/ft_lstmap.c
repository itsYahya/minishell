/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mrab <yel-mrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:18:00 by yel-mrab          #+#    #+#             */
/*   Updated: 2022/02/28 22:16:03 by yel-mrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_head;
	t_list	*new_node;

	head = lst;
	new_head = 0;
	while (head)
	{
		new_node = ft_lstnew((f)(head->content));
		if (new_node)
		{
			if (new_head == 0)
				new_head = new_node;
			else
				ft_lstadd_back(&new_head, new_node);
			head = head->next;
		}
		else
			ft_lstclear(&new_head, del);
	}
	return (new_head);
}
