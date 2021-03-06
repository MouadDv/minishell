/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 07:18:28 by milmi             #+#    #+#             */
/*   Updated: 2021/11/24 23:54:16 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_redir(t_red *redir)
{
	int		*tab;

	if (redir)
	{
		tab = ft_tab_of_in_out(redir);
		if (tab[0] != 1024 && tab[0] != -1 && g_data.flagerr == -1)
		{
			dup2(tab[0], 0);
			close(tab[0]);
		}
		if (tab[1] != 1024 && tab[1] != -1 && g_data.flagerr == -1)
		{
			dup2(tab[1], 1);
			close(tab[1]);
		}
		if (g_data.flagerr != -1)
		{
			ft_global_check_err_norm();
			g_data.statuscode = 1;
			return (1);
		}
	}
	return (0);
}

void	ft_child_redir(char **envp)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(g_data.ptrs[0], g_data.ptrs, envp);
	exit(g_data.statuscode);
}

void	ft_exec_cmd_redir(char **cmd, t_node *node)
{
	int		flag;
	char	**envp;

	g_data.path = ft_path(g_data.node);
	ft_builtins(cmd, node, &flag);
	g_data.ptrs = NULL;
	if (flag == 1)
		g_data.ptrs = ft_find_path(g_data.path, cmd);
	envp = env_gen(g_data.node);
	if (g_data.ptrs != NULL)
	{
		g_data.p1 = fork();
		if (g_data.p1 == -1)
			exit (EXIT_FAILURE);
		else if (g_data.p1 == 0)
			ft_child_redir(envp);
		else
			waitpid(g_data.p1, &g_data.statuscode, 0);
		free_envp(envp);
		free_envp(g_data.path);
	}
	signalhandling();
}

void	ft_exec_redirections(char **cmd, t_red *redir, t_node *node)
{
	int		ret;

	ret = 0;
	g_data.saved[0] = dup(0);
	g_data.saved[1] = dup(1);
	g_data.cmderr = NULL;
	g_data.flagerr = -1;
	g_data.fdin = 1024;
	g_data.fdout = 1024;
	ret = ft_dup_redir(redir);
	if (ret == 1)
		return ;
	if (g_data.statuscode != 1)
		ft_exec_cmd_redir(cmd, node);
	reset_dup();
}

void	ft_global_redir(t_cmd *strct, t_node *head)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	tmp2 = tmp->redirections;
	ft_exec_redirections(tmp->args, tmp2, head);
}
