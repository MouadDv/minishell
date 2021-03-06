/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impim_export_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:07:49 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/25 05:55:11 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(t_node *tmp1, t_node *tmp2)
{
	g_data.wrd = tmp1->name;
	tmp1->name = tmp2->name;
	tmp2->name = g_data.wrd;
	g_data.val = tmp1->val;
	tmp1->val = tmp2->val;
	tmp2->val = g_data.val;
}

void	ft_sort_list(t_node *head)
{
	int		len;
	int		i;
	t_node	*tmp1;
	t_node	*tmp2;

	i = 0;
	len = len_list(head);
	while (i < len)
	{
		tmp1 = head;
		if (tmp1 != NULL)
			tmp2 = tmp1->next;
		else
			tmp2 = NULL;
		while ((tmp1 != NULL) && (tmp2 != NULL))
		{
			if (ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name)) > 0)
				ft_swap(tmp1, tmp2);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		tmp1 = head;
		i++;
	}
}

t_node	*alloc_list(void)
{
	t_node	*newlist;

	newlist = (t_node *)malloc(sizeof(t_node));
	if (newlist == NULL)
		return (NULL);
	newlist->next = NULL;
	return (newlist);
}

t_node	*copy_list(t_node *node)
{
	t_node	*cur;
	t_node	*newlist;
	t_node	*tail;

	cur = node;
	newlist = NULL;
	tail = NULL;
	while (cur != NULL)
	{
		if (newlist == NULL)
		{
			newlist = alloc_list();
			tail = newlist;
		}
		else
		{
			tail->next = alloc_list();
			tail = tail->next;
		}
		tail->name = cur->name;
		tail->val = cur->val;
		cur = cur->next;
	}
	return (newlist);
}

int	ft_check_valid_identifier(char *name)
{
	int	i;

	i = 0;
	if (!((name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= 'A' && name[i] <= 'Z')
			|| name[i] == '_'))
		return (1);
	i++;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}
