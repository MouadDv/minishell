/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:27:13 by sbensarg          #+#    #+#             */
/*   Updated: 2021/10/26 19:40:56 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipes(t_node *node, t_cmd *strct)
{
	int   p[2];
	pid_t pid;
	int   fd_in = 0;
	char **ptrs;
	char **path;
	t_cmd	*tmp;
	t_red	*tmp2;
	

	tmp = strct;
	int i;
	int flag;
	
	flag = 0;
	path = ft_path(node);
	ptrs = malloc(sizeof(t_cmd));
	i = 0;
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
			tmp2 = tmp->redirections;
			if (tmp2)
			{
				while (tmp2)
				{
					if (tmp2->type == 'i' || tmp2->type == 'o' || tmp2->type == 'a' || tmp2->type == 'h')
					{	
						if (tmp2->type == 'i' || tmp2->type == 'o' || tmp2->type == 'a')
							ft_exec_child_redir(tmp->args, tmp2, node);
						if (tmp2->type == 'h')
							ft_exec_child_heredoc(tmp->args, tmp2, node);
					}
					tmp2 = tmp2->next;
				}
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