/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:49:48 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:49:51 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlengnl(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

void	*ft_memcpygnl(void *dest, char *src, size_t n)
{
	char	*psrc;
	char	*pdest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	psrc = (char *)src;
	pdest = (char *)dest;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}

char	*ft_strdupgnl(char *s1)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char ) * (ft_strlengnl(s1) + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpygnl(dest, s1, (ft_strlengnl(s1) + 1));
	return (dest);
}

char	*ft_strjoingnl(char **s1, char **s2)
{
	int		sum;
	char	*newstr;
	char	*str1;
	char	*str2;

	str1 = *s1;
	str2 = *s2;
	if (str1 == NULL || str2 == NULL)
		return (NULL);
	sum = ft_strlengnl((char *)str1) + ft_strlengnl((char *)str2);
	newstr = (char *)malloc(sum + 1);
	if (newstr == NULL)
		return (NULL);
	ft_memcpygnl(newstr, str1, ft_strlengnl(str1));
	ft_memcpygnl(newstr + ft_strlengnl(str1), str2, ft_strlengnl(str2) + 1);
	free(str1);
	return (newstr);
}

char	*ft_strchrgnl(const char *s, int c)
{
	while (*s != c && *s != '\0')
	{
		s++;
	}
	if (*s == c)
	{
		return ((char *)s);
	}
	else
	{
		return (NULL);
	}
}
