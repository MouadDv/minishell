/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:19:17 by chicky            #+#    #+#             */
/*   Updated: 2021/11/09 17:20:34 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_node *head)
{
	t_node	*temp;
	char	*ret;
	char	*value;
	int		i;
	

	i = 0;
	temp = head;
	g_data.statuscode = 0;
	while (temp != NULL)
	{	
		value = temp->val;
		ret = ft_substr(value, 2, (ft_strlen(value) - 3));
		if (ft_strlen(ret) != 0)
		{
			write(1, temp->name, ft_strlen(temp->name));
			write(1, "=", 1);
			write(1, ret, ft_strlen(ret));
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
}
