/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:41 by milmi             #+#    #+#             */
/*   Updated: 2021/11/15 03:48:32 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void	*buff)
{
	if (buff != NULL)
		free(buff);
	buff = NULL;
}

void	free_strct(t_cmd	*strct, t_red	*tmp, t_red	*tmp2, t_cmd	*tmp3)
{
	int	i;

	while (strct)
	{
		tmp3 = strct;
		tmp2 = strct->redirections;
		i = 0;
		free(strct->cmd);
		while (strct->args[i])
		{
			free_null(strct->args[i]);
			i++;
		}
		free_null(strct->args);
		while (tmp2)
		{
			tmp = tmp2;
			free_null(tmp2->arg);
			tmp2 = tmp2->next;
			free(tmp);
		}
		strct = strct->next;
		free(tmp3);
	}
}

void	free_node(t_node	*node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node;
		free_null(node->name);
		free_null(node->val);
		node = node->next;
		free_null(tmp);
	}
}

void	protection(t_cmd *strct)
{
	free_strct(strct, NULL, NULL, NULL);
	exit(1);
}
