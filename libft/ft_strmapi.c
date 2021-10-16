/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:11:35 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:11:38 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				j;
	unsigned char	*str;
	char			*ret;

	j = 0;
	str = (unsigned char *)s;
	if (!s)
		return (NULL);
	while (str[j] != '\0')
		j++;
	ret = (char *)malloc(sizeof(char) * j + 1);
	if (ret != NULL)
	{
		j = 0;
		while (str[j] != '\0')
		{
			ret[j] = f(j, str[j]);
			j++;
		}
		ret[j] = '\0';
		return (ret);
	}
	return (0);
}
