/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:07:03 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/25 05:58:31 by milmi            ###   ########.fr       */
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

void	check_ret_chdir(int ret, char *err)
{
	if (ret == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, err, ft_strlen(err));
		write(2, ": No such file or directory\n", 28);
		g_data.statuscode = 1;
	}
}

void	check_val_home(t_node *tmp, int *flag)
{
	int		ret;
	char	*home;

	home = ft_home(tmp);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, "HOME", ft_strlen(tmp->name)) == 0)
		{
			*flag = 1;
			if (ft_strncmp(tmp->val, "=\"\"", ft_strlen(tmp->val)) == 0)
				chdir(".");
			else
			{
				ret = chdir(home);
				check_ret_chdir(ret, home);
				free_null(home);
			}
			break ;
		}
		tmp = tmp->next;
	}
}

void	impli_cd_norm(t_node *tmp)
{
	int		flag;

	flag = 0;
	check_val_home(tmp, &flag);
	if (flag != 1)
	{
		write(2, "minishell: cd: « HOME » non défini\n", 38);
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
	{
		ret = chdir(ptr);
		check_ret_chdir(ret, ptr);
	}
}
