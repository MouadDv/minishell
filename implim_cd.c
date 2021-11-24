/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:03 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/24 03:20:41 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_home(t_node *head)
{
	t_node	*cur;
	char	*value;
	char	*ret;

	cur = head;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->name, "HOME", ft_strlen(cur->name)) == 0)
		{
			value = cur->val;
			ret = ft_substr(value, 2, (ft_strlen(value) - 3));
		}
		cur = cur->next;
	}
	return (ret);
}
void	impli_cd_norm(t_node *tmp)
{
	 char	*home;
	int			ret;
	int			flag;

	flag = 0;
	home = ft_home(tmp);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "HOME", strlen(tmp->name)) == 0)
		{
			flag = 1;
			if (ft_strncmp(tmp->val, "=\"\"", strlen(tmp->val)) == 0)
				chdir(".");
			else
			{
				ret = chdir(home);
				if (ret == -1)
				{
					write(2, "bash: cd: ", 10);
					write(2, home, ft_strlen(home));
					write(2, ": No such file or directory\n", 28);
					g_data.statuscode = 1;
				}
				free_null(home);
			}
			break ;
		}
		tmp = tmp->next;
	}
	if (flag != 1)
	{
		write(2, "bash: cd: « HOME » non défini\n", 33);
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
