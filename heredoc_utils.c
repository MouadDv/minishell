/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:30:31 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/23 12:28:01 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_heredoc(t_cmd *strct)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	while (tmp)
	{
		tmp2 = tmp->redirections;
		while (tmp2)
		{
			if (tmp2->type == 'h')
				return (1);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_search(t_red	*tmp2, char c)
{
	while (tmp2)
	{
		if (tmp2->type == c)
			return (1);
		tmp2 = tmp2->next;
	}
	return (0);
}

void	ft_thereishd(t_cmd *tmp)
{
	int	i;
	int	fd;

	i = 0;
	if (tmp->next == NULL && g_data.thereishd)
	{
		while (i < g_data.j)
		{
			g_data.filename = ft_strjoin("/tmp/tmpfile", ft_itoa(i));
			fd = open(g_data.filename, O_RDONLY, 0777);
			while (get_next_line(fd, &g_data.buff) > 0)
			{
				write(2, g_data.buff, ft_strlen(g_data.buff));
				write(2, "\n", 1);
			}
			close(fd);
			unlink(g_data.filename);
			i++;
		}
	}
}

void	ft_child_heredoc(t_red *tmp2)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, tmp2->arg, ft_strlen(tmp2->arg) + 1) == 0)
			break ;
		write(g_data.fd[1], line, ft_strlen(line));
		write(g_data.fd[1], "\n", 1);
		free(line);
	}
	exit(1);
}
