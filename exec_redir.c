/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 18:10:16 by chicky            #+#    #+#             */
/*   Updated: 2021/10/27 19:40:02 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_inputs(t_red *redir, int *flag)
{
	int fd;
	int i;
	t_red *tmp2;

	tmp2 = redir;
	i = 0;
	fd = -1;
	while (tmp2)
	{
		fd = open(tmp2->arg, O_RDONLY);
		if (fd < 0)
		{
			*flag = 1;
			perror("ERROR 1 ");
			exit (1);
		}
		tmp2 = tmp2->next;
	}
	return (fd);
}

int	check_outputs(t_red *redir, int *flag)
{
	int fd;
	int i;
	t_red *tmp2;

	tmp2 = redir;
	i = 0;
	fd = -1;
	while (tmp2)
	{
		fd = open(tmp2->arg, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (fd < 0)
		{
			*flag = 1;
			perror("ERROR 3 ");
			if (errno == 13)
				g_data.statuscode = 1;
			exit (1);
		}
		tmp2 = tmp2->next;
	}
	return (fd);
}
int	check_outputs_append(t_red *redir, int *flag)
{
	int		fd;
	int		i;
	t_red	*tmp2;

	tmp2 = redir;
	i = 0;
	fd = -1;
	while (tmp2)
	{
		fd = open(tmp2->arg, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (fd < 0)
		{
			*flag = 1;
			perror("ERROR 3 ");
			if (errno == 13)
				g_data.statuscode = 1;
			exit (1);
		}
		tmp2 = tmp2->next;
	}
	return (fd);
}

void 	ft_exec_child_redir(char **cmd, t_red *redir, t_node *head)
{
	int 	fdin;
	int		fdout;
	int		fdout_a;
	char	**path;
	int		flag;
	int		flag2;
	int		flag3;
	int		b_in;
	t_red	*tmp2;

	tmp2 = redir;
	b_in = 0;
	path = ft_path(head);
	if (tmp2->type == 'i')
	{
		fdin = check_inputs(redir, &flag);
		if (fdin != -1 && flag != 1)
		{
			dup2(fdin, 0);
			close(fdin);
		}
	}
	if (tmp2->type == 'o')
	{
		fdout = check_outputs(redir, &flag2);
		if (fdout != -1 && flag2 != 1)
		{
			dup2(fdout, 1);
			close(fdout);
		}
	}
	if (tmp2->type == 'a')
	{
		fdout_a = check_outputs_append(redir, &flag3);
		if (fdout_a != -1 && flag3 != 1)
		{
			dup2(fdout_a, 1);
			close(fdout_a);
		}
	}
	ft_builtins(cmd, head, &b_in);
	if (b_in == 1)
		cmd = ft_find_path(path, cmd);

	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

void 	ft_exec_child_heredoc(char **cmd, t_red *redir, t_node *head)
{
	int		fd[2];
	char	**path;
	int		b_in;
	char	*line;
	int		i;
	t_red	*tmp2;

	tmp2 = redir;
	i = 0;
	b_in = 0;
	path = ft_path(head);

	while (tmp2)
	{
		if (pipe(fd) == -1)
			exit (EXIT_FAILURE);
		while (1)
		{
			line = readline("heredoc>");
			if (ft_strncmp(line, tmp2->arg, ft_strlen(tmp2->arg) + 1) == 0)
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		tmp2 = tmp2->next;
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	ft_builtins(cmd, head, &b_in);
	if (b_in == 1)
	cmd = ft_find_path(path, cmd);
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}
