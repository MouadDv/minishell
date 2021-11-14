/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:01:59 by milmi             #+#    #+#             */
/*   Updated: 2021/11/14 04:03:42 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	max_long(int f)
{
	if (f == -1)
		return (0);
	else if (f == 1)
		return (-1);
	return (1);
}

long long	ft_atoi(const char *str)
{
	int				j;
	unsigned long	c;
	int				f;

	j = 0;
	f = 1;
	c = 0;
	while (str[j] == '\r' || str[j] == '\v' || str[j] == '\b'
		|| str[j] == '\f' || str[j] == '\t'
		|| str[j] == '\n' || str[j] == ' ')
		j++;
	if (str[j] == '+' && str[j + 1] != '-')
		j++;
	if (str[j] == '-')
	{
		f = -1;
		j++;
	}
	while (str[j] >= '0' && str[j] <= '9')
	{
		c = c * 10 + str[j++] - '0';
		if (c > 9223372036854775807)
			return (max_long(f));
	}
	return (c * f);
}
