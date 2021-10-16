/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:11:08 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:11:11 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*s;
	char	*d;
	int		j;
	int		k;
	size_t	ret;

	k = 0;
	d = (char *)dest;
	s = (char *)src;
	j = (int)ft_strlen(d);
	if (ft_strlen(d) > size)
		ret = size + ft_strlen(s);
	else
		ret = ft_strlen(d) + ft_strlen(s);
	while (k < (int)size - j - 1 && s[k] != '\0')
	{
		dest[j + k] = src[k];
		k++;
	}
	if (k <= (int)size && k)
		dest[j + k] = '\0';
	return (ret);
}
