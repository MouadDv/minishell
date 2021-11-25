/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:49:09 by chicky            #+#    #+#             */
/*   Updated: 2021/11/25 02:34:33 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_unset(char *name)
{
	write(2, "minishell: unset: « ", 21);
	write(2, name, ft_strlen(name));
	write(2, " » : identifiant non valable\n", 30);
	g_data.statuscode = 1;
}

void	ft_unset_norm(t_node *tmp, t_node **head)
{
	*head = (*head)->next;
	free_null(tmp->name);
	free_null(tmp->val);
	free(tmp);
}

void	ft_rm_element(t_node **head, char *name, t_node *tmp, t_node *cur)
{
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
				free_null(tmp->name);
				free_null(tmp->val);
				free(tmp);
				break ;
			}
			cur = cur->next;
		}
	}
}

void	ft_unset(t_node **head, char *name)
{
	t_node	*tmp;
	t_node	*cur;
	int		ret;

	g_data.statuscode = 0;
	cur = *head;
	tmp = NULL;
	ret = ft_check_valid_identifier(name);
	if (ret != 1)
		ft_rm_element(head, name, tmp, cur);
	else
		ft_err_unset(name);
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
