/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:31:16 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/13 07:08:01 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_ptr_exit(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		i++;
	}
	return (i);
}

int	is_digit(char *ptr)
{
	int	i;

	i = 0;
	if (ptr[i] == '-' || ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
		i++;
	if (ptr[i] != '\0')
		return (1);
	return (0);
}

void	ft_exit(char **ptr)
{
	int	s;
	int	nbr;
	int	i;
	int	ret;

	i = 1;
	g_data.statuscode = 0;
	s = size_ptr_exit(ptr);
	if (s == 2)
	{
		nbr = ft_atoi(ptr[1]);
		ret = is_digit(ptr[1]);
	}
	write(2, "exit\n", 6);
	if (s == 2 && ret == 0)
		exit (nbr % 256);
	if (s > 2 && ret == 0)
	{
		write(2, "bash: exit: too many arguments\n", 32);
		g_data.statuscode = 1;
	}
	else if (ret == 1)
	{
		write(2, "bash: exit: ", 13);
		write(2, ptr[1], ft_strlen(ptr[1]));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	else
		exit(0);
}
