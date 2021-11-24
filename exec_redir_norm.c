/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:22:54 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/24 07:13:58 by milmi            ###   ########.fr       */
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

void	canceling(int sig)
{
	if (sig == SIGINT)
	{
		exit(1);
	}
}

int	ft_ret_heredoc_fd(t_red *tmp2)
{
	int		fdin;
	int		status_code;
	pid_t	f;

	if (pipe(g_data.fd) == -1)
		exit (EXIT_FAILURE);
	f = fork();
	if (f == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		ft_child_heredoc(tmp2);
	}
	else
	{
		waitpid(f, &status_code, 0);
		close(g_data.fd[1]);
	}
	if (WIFSIGNALED(status_code))
	{
		g_data.statuscode = 1;
		if (WTERMSIG(status_code) == SIGINT)
			write(1, "heredoc>  \b\b\n", 13);
	}
	fdin = g_data.fd[0];
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
