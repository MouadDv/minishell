/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:49:56 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:51:30 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <stdlib.h>
# include <unistd.h>

size_t			ft_strlengnl(const char *str);
void			*ft_memcpygnl(void *dest, char *src, size_t n);
char			*ft_strjoingnl(char **s1, char **s2);
char			*ft_strchrgnl(const char *s, int c);
int				get_next_line(int fd, char **line);
char			*ft_strdupgnl(char *str1);
int				get_next_line_norm(int fd, char **rest, char **line);
int				ft_read_norm(char *buf, char *s, char **line, char **rest);
int				ft_read(int fd, char **rest, char **line);
int				verif_reste(char **rest, char **line);
int				verif_reste_norm(char **rest, char **line, char *s);
int				to_free(char **ptr);

#endif
