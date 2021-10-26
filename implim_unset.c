/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:49:09 by chicky            #+#    #+#             */
/*   Updated: 2021/10/26 15:40:44 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_node **head, char *name)
{
	t_node *tmp;
	t_node *cur;
	cur = *head;
	
	if (ft_strncmp((*head)->name, name, ft_strlen(name)) == 0)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
	else
	{
		while (cur->next != NULL)
		{
			if (ft_strncmp(cur->next->name, name, ft_strlen(name)) == 0)
			{
				tmp = cur->next;
				cur->next = cur->next->next;
				free(tmp);
				break ;
			}
			else
				cur = cur->next;	
		}
	}
	
}