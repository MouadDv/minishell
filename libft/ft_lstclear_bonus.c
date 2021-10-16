/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:04:14 by milmi             #+#    #+#             */
/*   Updated: 2021/06/04 19:54:20 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*nx;

	if (lst && del)
	{
		nx = *lst;
		while (nx != NULL)
		{
			temp = nx;
			nx = nx->next;
			del(temp->content);
			free(temp);
		}
		*lst = NULL;
	}
}
