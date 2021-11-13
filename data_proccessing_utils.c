/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proccessing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:33:47 by milmi             #+#    #+#             */
/*   Updated: 2021/11/12 04:33:49 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_val(char	*name, t_node	*node)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (node != NULL)
	{
		if (!ft_strncmp(name, node->name, ft_strlen(name) + 1))
		{
			ret = ft_strdup(node->val);
			break ;
		}
		node = node->next;
	}
	if (ret == NULL)
		ret = ft_strdup("");
	return (ret);
}
