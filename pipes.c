/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:27:13 by sbensarg          #+#    #+#             */
/*   Updated: 2021/10/30 18:58:04 by sbensarg         ###   ########.fr       */
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
	

	tmp = strct;
	flag = 0;
	path = ft_path(node);
	ptrs = malloc(sizeof(t_cmd));
	tmp2 = tmp->redirections;
	b_in = 0;
	flag = 0;
	tab = ft_tab_of_in_out(tmp2, &flag);
	i = 0;
	fd_in = 0;
	fprintf(stderr, "tab[0] = %d , tab[1] = %d\n", tab[0], tab[1]);
	while (tmp)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup2(fd_in, 0); 
			if (tmp->next != NULL)
			{
				dup2(p[1], 1);
				close(p[1]);
			}
			close(p[0]);
			if (fd_in == -1 && tmp->args[0])
				return ;

			if (tmp2)
			{
				if (tab[0] != 1024 && tab[0] != -1 && flag != 1)
				{
					dup2(tab[0], 0);
					close(tab[0]);
				}
				if (tab[1] != 1024 && tab[1] != -1 && flag != 1)
				{
					dup2(tab[1], 1);
					close(tab[1]);
				}
				ft_builtins(tmp->args, node, &b_in);
				if (b_in == 1)
					ptrs = ft_find_path(path, tmp->args);
				execve(ptrs[0], ptrs, NULL);
				exit(EXIT_FAILURE);	
			}
			else
			{
				ft_builtins(tmp->args, node, &flag);
				if (flag == 1)
					ptrs = ft_find_path(path, tmp->args);
				execve(ptrs[0], ptrs, NULL);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			close(p[1]);
			int fd_old = fd_in;
			if(fd_old != 0) 
				close(fd_old);
			fd_in = p[0];
			close(tab[0]);
			close(tab[1]);
			tab[0] = 1024;
			tab[1] = 1024;
				
		}
		tmp = tmp->next;
		i++;
	}
	int nbr_cmd;
	nbr_cmd = 0;
	while (nbr_cmd < i)
	{
		wait(NULL);
		nbr_cmd++;
	}	
}