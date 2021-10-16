/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:03:37 by milmi             #+#    #+#             */
/*   Updated: 2021/06/04 19:53:52 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mincase(long int min, int count, long int i, char *ret)
{
	if (min == 1)
		ret[0] = '-';
	count--;
	ret[count] = '\0';
	count--;
	while ((count >= 0 && min == 0) || (min == 1 && count > 0))
	{
		ret[count] = i % 10 + 48;
		i = i / 10;
		count--;
	}
	return (ret);
}

int	ft_intlen(long int i)
{
	int	count;

	count = 0;
	while (i != 0)
	{
		i = i / 10;
		count++;
	}
	return (count + 1);
}

char	*ft_itoa(int n)
{
	long int	i;
	long int	k;
	int			count;
	long int	min;
	char		*ret;

	count = 0;
	min = 0;
	k = n;
	if (n < 0)
	{
		count++;
		min = 1;
		k = k * -1;
	}
	if (n == 0)
		count++;
	i = k;
	count += ft_intlen(i);
	i = k;
	ret = malloc(count);
	if (ret)
		return (ft_mincase(min, count, i, ret));
	return (0);
}
