/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:27:13 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/20 17:43:50 by milmi            ###   ########.fr       */
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
	envp = env_gen(node);
	ft_builtins(tmp->args, node, &flag);
	if (flag == 1)
	{
		g_data.ptrs = ft_find_path(g_data.path, tmp->args);
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

void	ft_child_pipe(t_cmd	*tmp, t_red	*tmp2, t_node *node)
{
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

int		ft_search(t_red	*tmp2, char c)
{
	while (tmp2)
	{
		if (tmp2->type == c)
			return (1);
		tmp2 = tmp2->next;
	}
	return (0);
}
void	ft_pipes(t_node *node, t_cmd *strct)
{
	t_cmd	*tmp;
	t_red	*tmp2;
	int		i;
	int		flag;
	pid_t   pid[20];

	tmp = strct;
	flag = 0;
	i = 0;
	g_data.fd_in = 0;
	tmp2 = tmp->redirections;
	while (tmp)
	{
		pipe(g_data.p);
		g_data.pid = fork();
		pid[i] = g_data.pid;
		if (g_data.pid == -1)
			exit (EXIT_FAILURE);
		else if (g_data.pid == 0)
		{
			ft_child_pipe(tmp, tmp2, node);
		}
		else
		{
			if (tmp2 && ft_search(tmp2, 'h'))
				waitpid(g_data.pid, &g_data.statuscode, 0);
			ft_save_input_for_next_cmd();
		}
		tmp = tmp->next;
		i++;
	}
	int	j = 0;
	while (j < i)
	{
		waitpid(pid[j], &g_data.statuscode, 0);
		j++;
	}
	g_data.statuscode = WEXITSTATUS(g_data.statuscode);
}
