/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:31:51 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/09 14:03:14 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_err_redir(void)
{
	if (g_data.flagerr == 1)
	{
		write(2, "bash: ", 7);
		write(2, g_data.cmderr, ft_strlen(g_data.cmderr));
		write(2, ": No such file or directory\n", 29);
	}
	else if (g_data.flagerr == 2)
	{
		write(2, "bash: ", 7);
		write(2, g_data.cmderr, ft_strlen(g_data.cmderr));
		write(2, ": Is a Directory\n", 18);
	}
	else if (g_data.flagerr == 3)
	{
		write(2, "bash: ", 7);
		write(2, g_data.cmderr, ft_strlen(g_data.cmderr));
		write(2, ": Permission Denied\n", 20);
	}
}

void	ft_check_err_piped_redir(void)
{
	if (g_data.flagerr != -1)
	{
		ft_check_err_redir();
		g_data.statuscode = 1;
		exit(g_data.statuscode);
	}
}

void	ft_dup_redir_in_pipes(t_red	*redir)
{
	g_data.tab = ft_tab_of_in_out(redir);
	if (g_data.tab[0] != 1024 && g_data.tab[0] != -1 && g_data.flagerr == -1)
	{
		g_data.fd_in = g_data.tab[0];
		dup2(g_data.fd_in, 0);
		close(g_data.fd_in);
	}
	if (g_data.tab[1] != 1024 && g_data.tab[1] != -1 && g_data.flagerr == -1)
	{
		dup2(g_data.tab[1], 1);
		close(g_data.tab[1]);
	}
	else
		ft_check_err_piped_redir();
}
