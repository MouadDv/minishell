/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:27:13 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/25 05:32:35 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_multiple_pipe(t_cmd	*tmp)
{
	dup2(g_data.fd_in, 0);
	if (tmp->next != NULL)
	{
		dup2(g_data.p[1], 1);
		close(g_data.p[1]);
	}
	close(g_data.p[0]);
	if (g_data.fd_in == -1 && tmp->args[0])
		return ;
}

void	ft_exec_pipe(t_node *node, t_cmd *tmp)
{
	int		flag;
	char	**envp;

	flag = 0;
	g_data.path = ft_path(node);
	envp = env_gen(node);
	ft_thereishd(tmp);
	ft_builtins(tmp->args, node, &flag);
	if (flag == 1)
	{
		g_data.ptrs = ft_find_path(g_data.path, tmp->args);
		free_envp(g_data.path);
		execve(g_data.ptrs[0], g_data.ptrs, envp);
	}
	free_envp(envp);
	exit(g_data.statuscode);
}

void	ft_save_input_for_next_cmd(void)
{
	close(g_data.p[1]);
	g_data.fd_old = g_data.fd_in;
	if (g_data.fd_old != 0)
		close(g_data.fd_old);
	g_data.fd_in = g_data.p[0];
}

void	ft_child_pipe(t_cmd	*tmp, t_red	*tmp2, t_node *node, int j)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (tmp->next != NULL && g_data.thereishd)
	{
		g_data.filename = ft_strjoin("/tmp/tmpfile", ft_itoa(j));
		g_data.fdtmp = open(g_data.filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(g_data.fdtmp, 2);
		close(g_data.fdtmp);
	}
	tmp2 = tmp->redirections;
	g_data.cmderr = NULL;
	g_data.flagerr = -1;
	g_data.fdin = 1024;
	g_data.fdout = 1024;
	if (tmp2)
		ft_dup_redir_in_pipes(tmp2);
	ft_dup_multiple_pipe(tmp);
	ft_exec_pipe(node, tmp);
}

void	ft_pipes(t_node *node, t_cmd *strct)
{
	t_cmd	*tmp;
	t_red	*tmp2;
	int		flag;

	tmp = strct;
	flag = 0;
	g_data.i = 0;
	g_data.j = 0;
	g_data.fd_in = 0;
	tmp2 = NULL;
	if (if_heredoc(strct))
		g_data.thereishd = 1;
	ft_norm_pipes(tmp, tmp2, node);
	loop_pids();
	signalhandling();
}
