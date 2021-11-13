/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proccessing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:33:40 by milmi             #+#    #+#             */
/*   Updated: 2021/11/12 04:33:42 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flagging(char c, int *flag)
{
	if (c == '"' && *flag == 0)
		*flag = 2;
	else if (c == '"' && *flag == 2)
		*flag = 0;
	if (c == '\'' && *flag == 0)
		*flag = 1;
	else if (c == '\'' && *flag == 1)
		*flag = 0;
}

int	replace_env_norm(int flag, char	*lct, int i)
{
	if ((flag == 0 || flag == 2) && lct[i] == '$'
		&& ((lct[i + 1] >= 'a' && lct[i + 1] <= 'z')
			|| (lct[i + 1] >= 'A' && lct[i + 1] <= 'Z')
			|| lct[i + 1] == '_'))
	{
		*(lct + i) = '\0';
		return (1);
	}
	else
		return (0);
}

void	replace_env_norm2(char *val, char *name)
{
	free_null(val);
	free_null(name);
}

char	*replace_env(char *lct, char *tmp, t_node *node, int flag)
{
	s_rp	rp;

	rp.i = 0;
	rp.ret = ft_strdup("");
	while (lct[rp.i])
	{
		flagging(lct[rp.i], &flag);
		if (replace_env_norm(flag, lct, rp.i))
		{
			rp.ret = ft_strjoin1(rp.ret, tmp);
			rp.name = get_name(lct + rp.i + 1);
			tmp = lct + rp.i + 1 + ft_strlen(rp.name);
			rp.val = env_val(rp.name, node);
			if (ft_strlen(rp.val) > 0)
			{
				rp.val2 = ft_substr(rp.val, 2, ft_strlen(rp.val) - 3);
				rp.ret = ft_strjoin1(rp.ret, rp.val2);
				free_null(rp.val2);
			}
			replace_env_norm2(rp.val, rp.name);
		}
		rp.i++;
	}
	rp.ret = ft_strjoin1(rp.ret, tmp);
	return (rp.ret);
}

void	data_proc(t_cmd	*strct, t_node	*node)
{
	int		i;
	t_red	*tmp2;
	char	*str;

	while (strct)
	{
		tmp2 = strct->redirections;
		i = 0;
		while (strct->args[i])
		{
			str = strct->args[i];
			strct->args[i] = replace_env(str, str, node, 0);
			free_null(str);
			i++;
		}
		while (tmp2)
		{
			str = tmp2->arg;
			tmp2->arg = replace_env(str, str, node, 0);
			free_null(str);
			tmp2 = tmp2->next;
		}
		strct = strct->next;
	}
}
