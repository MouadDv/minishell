/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:10:16 by chicky            #+#    #+#             */
/*   Updated: 2021/11/06 00:51:41 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_dup(void)
{
	dup2(g_data.saved[0], 0);
	dup2(g_data.saved[1], 1);
}

int	*ft_tab_of_in_out(t_red *redir, int *flag)
{
	t_red *tmp2;
	int fdin;
	int fdout;
	int	fd[2];
	char *line;
	int *tab;

	tmp2 = redir;
	fdin = 1024;
	fdout = 1024;
	tab = malloc(sizeof(char) * 2);
	g_data.cmderr = malloc(sizeof(tmp2->arg));
	g_data.cmderr = NULL;
	g_data.flagerr = -1;

	while (tmp2 != NULL)
	{
		if (tmp2->type == 'i')
		{
			fdin = open(tmp2->arg, O_RDONLY);
			if (fdin)
			{
				if (fdin < 0)
				{
					if (g_data.cmderr == NULL)
						g_data.cmderr = tmp2->arg;
					if (errno == 13)
					{
						if(g_data.flagerr == -1) 
							g_data.flagerr = 3;
					}
					else if (g_data.flagerr == -1)
					{
						g_data.flagerr = 1;
					}
				}
				else if (open(tmp2->arg, O_DIRECTORY) > 0)
				{
					if (g_data.cmderr == NULL)
						g_data.cmderr = tmp2->arg;
					if(g_data.flagerr == -1) 
						g_data.flagerr = 2;
				}
			}
		}
		if (tmp2->type == 'h')
		{
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
		}
		if (tmp2->type == 'o')
		{
			fdout = open(tmp2->arg, O_CREAT | O_TRUNC | O_RDWR, 0777);
			if (fdout < 0)
			{
				if (g_data.cmderr == NULL)
					g_data.cmderr = tmp2->arg;
				if (errno == 13)
				{
					if(g_data.flagerr == -1) 
						g_data.flagerr = 3;
				}
				else if (open(tmp2->arg, O_DIRECTORY) > 0)
				{
					if(g_data.flagerr == -1) 
						g_data.flagerr = 2;
				}
				else if (g_data.flagerr == -1)
				{
					g_data.flagerr = 1;
				}
				break;
			}
		}
		if (tmp2->type == 'a')
		{
			fdout = open(tmp2->arg, O_CREAT | O_APPEND | O_RDWR, 0777);
			if (fdout < 0)
			{
			
				if (g_data.cmderr == NULL)
					g_data.cmderr = tmp2->arg;
				
				if (errno == 13)
				{
					if(g_data.flagerr == -1) 
						g_data.flagerr = 3;
				}
				else if (open(tmp2->arg, O_DIRECTORY) > 0)
				{
					if(g_data.flagerr == -1) 
						g_data.flagerr = 2;
				}
				else if (g_data.flagerr == -1)
				{
					g_data.flagerr = 1;
				}
				break;
			}
		}
		tmp2 = tmp2->next;
	}

	tab[0] = fdin;
	tab[1] = fdout;
	return(tab);
}

void	ft_exec_redirections(char **cmd, t_red *redir, t_node *node)
{
	char	**path;
	int		b_in;
	int		flag;
	int		p;
	int		*tab;

	char	**ptrs;
	int		scode;
	ptrs = malloc(sizeof(t_cmd));
	path = ft_path(node);
	
	g_data.saved[0] = dup(0);
	g_data.saved[1] = dup(1);
	
	if (redir)
	{
		tab = ft_tab_of_in_out(redir, &flag);
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
				return ;
			}
		}
		ft_builtins(cmd, node, &flag);
		if (flag == 1)
			ptrs = ft_find_path(path, cmd);
		if (ptrs != NULL)
		{
			p = fork();
			if (p == -1)
				exit (EXIT_FAILURE);
			else if (p == 0)
			{
				execve(ptrs[0], ptrs, NULL);
				exit(g_data.statuscode);
			}
			else
			{
				waitpid(p, &g_data.statuscode, 0);
			}	
		}
		g_data.statuscode =  WEXITSTATUS(g_data.statuscode);
		reset_dup();
}

void ft_global_redir(t_cmd *strct, t_node *head)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	tmp2 = tmp->redirections;

	ft_exec_redirections(tmp->args,tmp2, head);
}
