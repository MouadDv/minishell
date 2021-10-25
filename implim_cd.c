/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:03 by sbensarg          #+#    #+#             */
/*   Updated: 2021/10/25 21:01:50 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	impli_cd(char *ptr, t_node *node)
{
	const char *home;
	int ret;
	int i;
	t_node *tmp;
	int	flag;
	
	i = 0;
	tmp = node;
	flag = 0;
	home = getenv("HOME");
	if (ptr == NULL || *ptr == ' ' || *ptr == '\0')
	{
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->name, "HOME", strlen(tmp->name)) == 0)
			{
				flag = 1;
				if (ft_strncmp(tmp->val, "=\"\"", strlen(tmp->val)) == 0)
			 		chdir(".");
				else
					ret = chdir(home);
				break ;
			}
			tmp = tmp->next;
		}
		if (flag != 1)
			printf ("bash: cd: « HOME » non défini\n");
	}
	else
	{
			ret = chdir(ptr);
	}
}
