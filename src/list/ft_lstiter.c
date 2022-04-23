/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mrab <yel-mrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:47:35 by yel-mrab          #+#    #+#             */
/*   Updated: 2022/02/28 22:15:32 by yel-mrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	ft_lstiter(t_list *node, void (*f)(void *))
{
	t_list	*head;

	head = node;
	while (head)
	{
		(*f)(head->content);
		head = head->next;
	}
}
