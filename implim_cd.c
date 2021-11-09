/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:03 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/09 16:22:57 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	impli_cd_norm(t_node *tmp)
{
	const char	*home;
	int			ret;
	int			flag;

	flag = 0;
	home = getenv("HOME");
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
	{
		printf ("bash: cd: « HOME » non défini\n");
		g_data.statuscode = 1;
	}
}

void	impli_cd(char *ptr, t_node *node)
{
	int		ret;
	t_node	*tmp;

	g_data.statuscode = 0;
	tmp = node;
	if (ptr == NULL || *ptr == ' ' || *ptr == '\0')
		impli_cd_norm(tmp);
	else
		ret = chdir(ptr);
}
