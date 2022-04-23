/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mrab <yel-mrab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:30:58 by yel-mrab          #+#    #+#             */
/*   Updated: 2022/02/28 22:16:10 by yel-mrab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	ft_lstsize(t_list *head)
{
	int		index;
	t_list	*temp;

	index = 0;
	temp = head;
	while (temp)
	{
		index++;
		temp = temp->next;
	}
	return (index);
}
