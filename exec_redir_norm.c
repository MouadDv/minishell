/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:54 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/09 20:28:53 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ret_input_fd(t_red *tmp2)
{
	int	fdin;

	fdin = open(tmp2->arg, O_RDONLY);
	if (fdin)
	{
		if (fdin < 0)
		{
			if (g_data.cmderr == NULL)
				g_data.cmderr = tmp2->arg;
			ft_check_err_norm();
		}
		else if (open(tmp2->arg, O_DIRECTORY) > 0)
		{
			if (g_data.cmderr == NULL)
				g_data.cmderr = tmp2->arg;
			if (g_data.flagerr == -1)
				g_data.flagerr = 2;
		}
	}
	return (fdin);
}

int	ft_ret_heredoc_fd(t_red *tmp2)
{
	int		fd[2];
	char	*line;
	int		fdin;

	if (pipe(fd) == -1)
	{
		exit (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, tmp2->arg, ft_strlen(tmp2->arg) + 1) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	fdin = fd[0];
	return (fdin);
}

int	ft_ret_outputfd(t_red *tmp2)
{
	int	fdout;

	fdout = open(tmp2->arg, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fdout < 0)
	{
		if (g_data.cmderr == NULL)
			g_data.cmderr = tmp2->arg;
		ft_check_err_norm2(tmp2);
	}
	return (fdout);
}

int	ft_ret_appendfd(t_red *tmp2)
{
	int	fdout;

	fdout = open(tmp2->arg, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fdout < 0)
	{
		if (g_data.cmderr == NULL)
			g_data.cmderr = tmp2->arg;
		ft_check_err_norm2(tmp2);
	}
	return (fdout);
}

void	ft_tab_of_in_out_norm(t_red *tmp2)
{
	while (tmp2 != NULL)
	{
		if (tmp2->type == 'i')
		{
			g_data.fdin = ft_ret_input_fd(tmp2);
			if (g_data.fdin < 0)
				break ;
		}
		if (tmp2->type == 'h')
			g_data.fdin = ft_ret_heredoc_fd(tmp2);
		if (tmp2->type == 'o')
		{
			g_data.fdout = ft_ret_outputfd(tmp2);
			if (g_data.fdout < 0)
				break ;
		}
		if (tmp2->type == 'a')
		{
			g_data.fdout = ft_ret_appendfd(tmp2);
			if (g_data.fdout < 0)
				break ;
		}
		tmp2 = tmp2->next;
	}
}
