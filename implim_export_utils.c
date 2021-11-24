/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:38:08 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/24 01:18:28 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(t_node **head, char *name, char *val, int *flag)
{
	t_node	*cur;

	cur = *head;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->name, name, ft_strlen(name)) == 0)
		{
			*flag = 2;
			if (cur->val != NULL && *val != '\0')
			{
				free(cur->val);
				cur->val = ft_strdup(val);
			}
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	len_list(t_node *head)
{
	t_node	*cur;
	int		i;

	cur = head;
	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}
