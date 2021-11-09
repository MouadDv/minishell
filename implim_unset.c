/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:49:09 by chicky            #+#    #+#             */
/*   Updated: 2021/11/09 20:17:58 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_norm(t_node *tmp, t_node **head)
{
	*head = (*head)->next;
	free(tmp);
}	

void	ft_unset(t_node **head, char *name)
{
	t_node	*tmp;
	t_node	*cur;
	int		i;

	i = 1;
	g_data.statuscode = 0;
	cur = *head;
	if (ft_strncmp((*head)->name, name, ft_strlen(name)) == 0)
	{
		tmp = *head;
		ft_unset_norm(tmp, head);
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
			}
				cur = cur->next;
		}
	}
}

void	ft_unset_global(t_node **head, char **ptr)
{
	int	i;

	i = 1;
	while (ptr[i])
	{
		ft_unset(head, ptr[i]);
		i++;
	}
}
