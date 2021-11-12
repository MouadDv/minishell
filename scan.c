/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:35:20 by milmi             #+#    #+#             */
/*   Updated: 2021/11/12 04:37:49 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_scan_b(char *str, int *i, int j)
{
	if (str[j] == '<' || str[j] == '>')
	{
		if (str[j] == str[j + 1])
			j++;
		while (str[j + 1] != '\0' && str[j + 1] == ' ')
			j++;
		if (str[j + 1] == '>' || str[j + 1] == '<'
			|| str[j + 1] == '|' || str[j + 1] == '\0')
		{
			*i = j;
			return (0);
		}
	}
	if (str[j] == '|')
	{
		while (str[j + 1] && str[j + 1] == ' ')
			j++;
		if (str[j + 1] == '|' || str[j + 1] == '\0')
		{
			*i = j;
			return (0);
		}
	}
	*i = j;
	return (1);
}

int	scan(char *str)
{
	int		i;
	char	c;
	int		ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[i + 1] != '\0' && str[i + 1] != c)
				i++;
			if (str[i + 1] == c)
				i += 2;
			if (str[i] == '\0')
				break ;
		}
		ret = ft_scan_b(str, &i, i);
		if (ret == 0)
			return (0);
		i++;
	}
	return (1);
}
