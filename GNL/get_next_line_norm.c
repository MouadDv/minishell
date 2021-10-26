/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_norm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:49:36 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:51:45 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	verif_reste_norm(char **rest, char **line, char *s)
{
	char	*tmp;

	*s = '\0';
	*line = ft_strdupgnl(*rest);
	if (*line == NULL)
		return (0);
	tmp = *rest;
	*rest = ft_strdupgnl(s + 1);
	if (*rest == NULL)
		return (0);
	to_free(&tmp);
	return (1);
}

int	ft_read_norm(char *buf, char *s, char **line, char **rest)
{
	to_free(&buf);
	*s = '\0';
	*line = *rest;
	*rest = ft_strdupgnl(s + 1);
	if (*rest == NULL)
		return (-1);
	return (1);
}

int	get_next_line_norm(int fd, char **rest, char **line)
{
	int	j;

	j = ft_read(fd, rest, line);
	if (j == -1)
		return (to_free(rest));
	if (*rest && j == 0)
	{
		*line = ft_strdupgnl(*rest);
		if (*line == NULL)
			return (-1);
		to_free(rest);
		return (0);
	}
	return (j);
}
