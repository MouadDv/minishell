/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:08:01 by milmi             #+#    #+#             */
/*   Updated: 2019/11/09 15:08:04 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	pos;
	long int	mod;
	long int	div;

	pos = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		pos = pos * -1;
	}
	else
		pos = n;
	if (pos <= 9)
	{
		pos = pos + 48;
		write(fd, &pos, 1);
	}
	else
	{
		div = pos / 10;
		mod = pos % 10 + 48;
		ft_putnbr_fd(div, fd);
		write(fd, &mod, 1);
	}
}
