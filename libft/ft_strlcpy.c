/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:11:16 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:11:19 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		j;
	size_t	i;

	j = 0;
	i = 0;
	if (dest == NULL || src == NULL)
		return (0);
	while (src[j] != '\0')
		j++;
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > i)
		dest[i] = '\0';
	return (j);
}
