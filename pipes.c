/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:27:13 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/06 00:09:39 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes(t_node *node,t_cmd *strct)
{
	int		p[2];
	pid_t	pid;
	int  	fd_in;
	char	**ptrs;
	char	**path;
	t_cmd	*tmp;
	t_red	*tmp2;
	int		i;
	int		flag;
	int		*tab;
	int		b_in;
	int		scode;

	tmp = strct;
	flag = 0;
	path = ft_path(node);
	ptrs = malloc(sizeof(t_cmd));
	b_in = 0;
	flag = 0;
	i = 0;
	fd_in = 0;
	tmp2 = tmp->redirections;
		
	while (tmp)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			tmp2 = tmp->redirections;
			if (tmp2)
			{
				tab = ft_tab_of_in_out(tmp2, &flag);
				if (tab[0] != 1024 && tab[0] != -1 && g_data.flagerr == -1)
				{
					fd_in = tab[0];
					dup2(fd_in, 0);
					close(fd_in);				
				}
				if (tab[1] != 1024 && tab[1] != -1 && g_data.flagerr == -1)
				{
					dup2(tab[1], 1);
					close(tab[1]);
				}
				else
				{
					if (g_data.flagerr != -1)
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
						g_data.statuscode = 1;
						exit(g_data.statuscode);
					}
				}
			}
			dup2(fd_in, 0); 
			if (tmp->next != NULL)
			{
				dup2(p[1], 1);
				close(p[1]);
			}
			close(p[0]);
			if (fd_in == -1 && tmp->args[0])
				return ;
			ft_builtins(tmp->args, node, &flag);
			if (flag == 1)
				ptrs = ft_find_path(path, tmp->args);
			
				execve(ptrs[0], ptrs, NULL);
				exit(g_data.statuscode);
		}
		else
		{
			waitpid(pid, &g_data.statuscode, 0);
			close(p[1]);
			int fd_old = fd_in;
			if(fd_old != 0) 
				close(fd_old);
			fd_in = p[0];
		}
		tmp = tmp->next;
		i++;
	}
	g_data.statuscode =  WEXITSTATUS(g_data.statuscode);
}