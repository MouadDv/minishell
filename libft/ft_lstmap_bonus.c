/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:05:02 by milmi             #+#    #+#             */
/*   Updated: 2021/06/04 20:02:40 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*iter;
	t_list	*temp;

	if (lst && f && del)
	{
		head = malloc(sizeof(t_list));
		head->content = f(lst->content);
		iter = head;
		temp = lst->next;
		while (temp != NULL)
		{
			iter->next = malloc(sizeof(t_list));
			if (!iter->next)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			iter->next->content = f(temp->content);
			iter = iter->next;
			temp = temp->next;
		}
		return (head);
	}
	return (NULL);
}
