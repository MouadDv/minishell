/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 22:52:22 by chicky            #+#    #+#             */
/*   Updated: 2021/10/26 15:45:51 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_global_echo(char **ptr)
{
	int m;
	int opt;

	m = 0;
	opt = 0;
	m = ft_echo_utils(ptr, &opt);
	if (m != 0)
		ft_echo(ptr, m, &opt);
}

int ft_echo_utils(char **ptr, int *opt)
{
	int i;
	int	k;
	int m;

	m = 0;
	i = 1;

	if (ptr[i])
	{
		while (ptr[i])
		{
			k = 0;
			if (ptr[i][k] == '-')
			{
				if (ptr[i][k + 1] == 'n')
				{
					while (ptr[i][k + 1] == 'n')
						k++;
				}
				else
				{
					m = i;
					break ;
				}
					
				if (ptr[i][k + 1] != '\0')
				{
					m = i;
					break;
				}
				else
					*opt = 1;
			}
			else
			{
				m = i;
				break ;
			}
			i++;
		}
	}
	else
		write(1, "\n", 1);
	return (m);
}

void ft_echo(char **ptr, int m, int *opt)
{	
	while (ptr[m])
	{
		write(1, ptr[m], ft_strlen(ptr[m]));
		if (ptr[m + 1])
			write(1, " ", 1);
		m++;
	}
	if (*opt != 1)
		write(1, "\n", 1);
}