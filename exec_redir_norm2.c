/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_norm2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:28:44 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/08 12:45:45 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_dup(void)
{
	dup2(g_data.saved[0], 0);
	dup2(g_data.saved[1], 1);
}

void	ft_check_err_norm(void)
{
	if (errno == 13)
	{
		if (g_data.flagerr == -1)
			g_data.flagerr = 3;
	}
	else if (g_data.flagerr == -1)
	{
		g_data.flagerr = 1;
	}
}

void	ft_check_err_norm2(t_red *tmp2)
{
	if (errno == 13)
	{
		if (g_data.flagerr == -1)
			g_data.flagerr = 3;
	}
	else if (open(tmp2->arg, O_DIRECTORY) > 0)
	{
		if (g_data.flagerr == -1)
			g_data.flagerr = 2;
	}
	else if (g_data.flagerr == -1)
	{
		g_data.flagerr = 1;
	}
}

void	ft_print_err_msg(char *msg)
{
	write(2, "bash: ", 7);
	write(2, g_data.cmderr, ft_strlen(g_data.cmderr));
	write(2, msg, ft_strlen(msg));
}

void	ft_global_check_err_norm(void)
{
	if (g_data.flagerr == 1)
		ft_print_err_msg(": No such file or directory\n");
	else if (g_data.flagerr == 2)
		ft_print_err_msg(": Is a Directory\n");
	else if (g_data.flagerr == 3)
		ft_print_err_msg(": Permission Denied\n");
}
