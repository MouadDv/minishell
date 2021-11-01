/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:10:16 by chicky            #+#    #+#             */
/*   Updated: 2021/11/01 17:23:54 by sbensarg         ###   ########.fr       */
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
	int	fd[2];
	int fdin;
	int fdout;
	char *line;
	int *tab;

	tmp2 = redir;
	fdin = 1024;
	fdout = 1024;
	tab = malloc(sizeof(char) * 2);

	while (tmp2 != NULL)
	{
		if (tmp2->type == 'i')
		{
			fdin = open(tmp2->arg, O_RDONLY);
			if (fdin < 0)
			{
				*flag = 1;
				write(2, "bash: ", 7);
				write(2, tmp2->arg, ft_strlen(tmp2->arg));
				perror("");
				exit (1);
			}
		}
		if (tmp2->type == 'h')
		{
			if (pipe(fd) == -1)
			{
				*flag = 1;
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
				*flag = 1;
				write(2, "bash: ", 7);
				write(2, tmp2->arg, ft_strlen(tmp2->arg));
				perror("");
				if (errno == 13)
					g_data.statuscode = 1;
				exit (1);
			}
		}
		if (tmp2->type == 'a')
		{
			fdout = open(tmp2->arg, O_CREAT | O_APPEND | O_RDWR, 0777);
			if (fdout < 0)
			{
				*flag = 1;
				write(2, "bash: ", 7);
				write(2, tmp2->arg, ft_strlen(tmp2->arg));
				perror("");
				if (errno == 13)
					g_data.statuscode = 1;
				exit (1);
			}
		}
		tmp2 = tmp2->next;
	}
	tab[0] = fdin;
	tab[1] = fdout;
	return(tab);
}

void 	ft_exec_redir(char **cmd, t_cmd *strct, t_node *head)
{
	char	**path;
	int		b_in;
	int		flag;
	int		p;
	int		*tab;
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	b_in = 0;
	flag = 0;
	path = ft_path(head);
	ft_builtins(cmd, head, &b_in);
	if (b_in == 1)
		cmd = ft_find_path(path, cmd);
	p = fork();
	if (p == -1)
		exit (EXIT_FAILURE);
	else if (p == 0)
	{
		while (tmp)
		{
			tmp2 = tmp->redirections;
			while(tmp2)
			{
				tab = ft_tab_of_in_out(tmp2, &flag);
				if (tab[0] != 1024 && tab[0] != -1 && flag != 1 && flag != 2)
				{
					dup2(tab[0], 0);
					close(tab[0]);
				}
				if (tab[1] != 1024 && tab[1] != -1 && flag != 3 && flag != 4)
				{
					dup2(tab[1], 1);
					close(tab[1]);
				}
				execve(cmd[0], cmd, NULL);
				exit(EXIT_FAILURE);
				tmp2 = tmp2->next;
			}
			tmp = tmp->next;
		}
	
	}
	else
	{
		wait(NULL);
	}
}

void ft_global_redir(t_cmd *strct, t_node *head)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	tmp2 = tmp->redirections;
	t_node *t;
	t = head;

	ft_exec_redir(tmp->args, strct, head);
}
