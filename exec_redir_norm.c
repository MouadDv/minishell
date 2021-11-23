/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:54 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/20 17:03:28 by milmi            ###   ########.fr       */
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
	pid_t	f;

	if (pipe(fd) == -1)
	{
		exit (EXIT_FAILURE);
	}
	f = fork();
	if (f == 0)
	{
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
	int	var;

	var = 0;
	while (tmp2 != NULL)
	{
		if (tmp2->type == 'i')
		{
			if (var == 0)
				ft_check_var_input(tmp2, &var);
		}
		if (tmp2->type == 'h')
			g_data.fdin = ft_ret_heredoc_fd(tmp2);
		if (tmp2->type == 'o')
		{
			if (var == 0)
				ft_check_var_output(tmp2, &var);
		}
		if (tmp2->type == 'a')
		{
			if (var == 0)
				ft_check_var_append(tmp2, &var);
		}
		tmp2 = tmp2->next;
	}
}
