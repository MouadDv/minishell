/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proccessing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:33:47 by milmi             #+#    #+#             */
/*   Updated: 2021/11/17 07:59:51 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*statuschar(void)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(g_data.statuscode);
	tmp2 = tmp;
	tmp = ft_strjoin("=\"", tmp);
	free(tmp2);
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, "\"");
	free(tmp2);
	return (tmp);
}

char	*env_val(char *name, t_node *node)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!ft_strncmp(name, "?", 2))
	{
		ret = statuschar();
		return (ret);
	}
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
