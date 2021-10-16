/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:05:58 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:06:02 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int k, size_t n)
{
	size_t			j;
	unsigned char	*str;
	unsigned char	c;

	j = 0;
	str = (unsigned char *)s;
	c = (unsigned char)k;
	n--;
	while (str[j] != c && n > j)
	{
		j++;
	}
	if (str[j] == c)
		return (str + j);
	return (0);
}
