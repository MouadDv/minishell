/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:13:03 by milmi             #+#    #+#             */
/*   Updated: 2021/06/04 20:16:59 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findstr(char *n, char *h, size_t j, size_t len)
{
	size_t	i;

	i = 0;
	while (n[i] == h[j] && n[i] != '\0' && j < len)
	{
		i++;
		j++;
	}
	if (n[i] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	j;
	size_t	i;
	size_t	ret;

	j = 0;
	i = 0;
	h = (char *)haystack;
	n = (char *)needle;
	if (!*needle)
		return (h);
	while (j + 1 < len && h[j] != '\0')
	{
		ret = j;
		if (ft_findstr(n, h, j, len) == 1)
			return (h + ret);
		i = 0;
		j++;
	}
	return (0);
}
