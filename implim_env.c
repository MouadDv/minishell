/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 23:19:17 by chicky            #+#    #+#             */
/*   Updated: 2021/11/19 21:29:14 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_node *head)
{
	t_node	*temp;
	char	*ret;
	int		i;

	i = 0;
	temp = head;
	ret = NULL;
	g_data.statuscode = 0;
	while (temp != NULL)
	{	
		if (ft_strlen(temp->val) == 0)
			ret = ft_strdup("");
		else
			ret = ft_substr(temp->val, 2, (ft_strlen(temp->val) - 3));
		if (ft_strlen(ret) != 0)
		{
			write(1, temp->name, ft_strlen(temp->name));
			write(1, "=", 1);
			write(1, ret, ft_strlen(ret));
			write(1, "\n", 1);
		}
		temp = temp->next;
		free(ret);
	}

}
