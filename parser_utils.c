/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:55 by milmi             #+#    #+#             */
/*   Updated: 2021/11/12 04:37:28 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_delimiter(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '|' && str[i] != '<'
		&& str[i] != '>' && str[i] != ' ')
		i++;
	return (i);
}

void	subarg(int *r, int i, char *str, t_red *red)
{
	int	end;

	while (str[i] == ' ' && str[i])
		i++;
	end = end_of_delimiter(str + i);
	red->arg = ft_substr(str, i, end);
	*r = *r + i + end - 1;
}

char	*ft_strjoin1(char *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	int		sum;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = strlen((char *)s1);
	lens2 = strlen((char *)s2);
	sum = lens1 + lens2;
	newstr = (char *)malloc(sum + 1);
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, s1, lens1);
	ft_memcpy(newstr + lens1, s2, lens2 + 1);
	free_null(s1);
	return (newstr);
}
