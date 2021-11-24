/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmquotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:39:14 by milmi             #+#    #+#             */
/*   Updated: 2021/11/24 03:55:58 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	*quotes_index(char *str, int i)
{
	size_t	*ret;
	int		flag;
	char	c;

	ret = malloc(2 * sizeof(size_t));
	flag = 0;
	while (str[i])
	{
		if (flag == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			flag = 1;
			c = str[i];
			ret[0] = i;
		}
		else if (flag == 1 && str[i] == c)
		{
			ret[1] = i;
			return (ret);
		}
		i++;
	}
	ret[1] = INT32_MAX;
	return (ret);
}

char	*get_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

char	*ft_rm_norm(char *r, char *str)
{
	char	*sub;
	char	*ret;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			break ;
		i++;
	}
	sub = ft_substr(str, 0, i);
	ret = ft_strjoin1(r, sub);
	free(sub);
	return (ret);
}

char	*rm_quotes2(char *str, int tmp, char *sub, char *ret)
{
	size_t	*i;

	i = quotes_index(str, 0);
	ret = get_str(str);
	while (i[1] < ft_strlen(str))
	{
		sub = ft_substr(str, i[0] + 1, i[1] - i[0] - 1);
		ret = ft_strjoin1(ret, sub);
		free(sub);
		tmp = i[1];
		if (str[tmp + 1] && str[tmp + 1] != '\'' && str[tmp + 1] != '"')
			ret = ft_rm_norm(ret, str + tmp + 1);
		free(i);
		i = quotes_index(str, tmp + 1);
	}
	free(i);
	if (sub == NULL)
	{
		free(ret);
		ret = str;
	}
	else
		free(str);
	return (ret);
}

void	rm_quotes(t_cmd *strct)
{
	int		i;
	t_red	*tmp2;

	while (strct)
	{
		tmp2 = strct->redirections;
		i = 0;
		while (strct->args && strct->args[i])
		{
			strct->args[i] = rm_quotes2(strct->args[i], 0, NULL, NULL);
			i++;
		}
		while (tmp2)
		{
			tmp2->arg = rm_quotes2(tmp2->arg, 0, NULL, NULL);
			tmp2 = tmp2->next;
		}
		strct = strct->next;
	}
}
