/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:06:22 by milmi             #+#    #+#             */
/*   Updated: 2021/06/04 20:09:23 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	j;
	char	*p;
	char	*s;

	j = 0;
	p = (char *) dest;
	s = (char *) src;
	if (p == NULL && s == NULL)
		return (0);
	if (dest == src)
		return (0);
	while (j < n)
	{
		p[j] = s[j];
		j++;
	}
	return (dest);
}
