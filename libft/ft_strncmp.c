/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:11:45 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:11:48 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	if (n == 0)
		return (0);
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && n > i + 1)
		i++;
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
