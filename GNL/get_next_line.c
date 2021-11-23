/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:49:19 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:49:23 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	to_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (-1);
}

int	verif_reste(char **rest, char **line)
{
	char	*s;

	if (!*rest)
	{
		*rest = ft_strdupgnl("");
		if (*rest == NULL)
			return (0);
	}
	else
	{
		s = ft_strchrgnl(*rest, '\n');
		if (s)
			return (verif_reste_norm(rest, line, s));
	}
	return (-1);
}

int	ft_read(int fd, char **rest, char **line)
{
	char	*buf;
	int		j;
	char	*s;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (-1);
	j = read(fd, buf, BUFFER_SIZE);
	while (j > 0)
	{
		buf[j] = '\0';
		*rest = ft_strjoingnl(rest, &buf);
		if (*rest == NULL)
			return (-1);
		s = ft_strchrgnl(*rest, '\n');
		if (s)
			return (ft_read_norm(buf, s, line, rest));
		j = read(fd, buf, BUFFER_SIZE);
	}
	to_free(&buf);
	return (j);
}

int	get_next_line(int fd, char **line)
{
	static char	*rest;
	int			k;

	if (fd < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	k = verif_reste(&rest, line);
	if (k == 0)
		return (-1);
	else if (k == 1)
		return (1);
	return (get_next_line_norm(fd, &rest, line));
}
