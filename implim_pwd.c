/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:00:49 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/09 17:21:05 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[MAXPATHLEN];
	char	*ret_getcwd;

	g_data.statuscode = 0;
	ret_getcwd = getcwd(buf, MAXPATHLEN);
	write(1, ret_getcwd, strlen(ret_getcwd));
	write(1, "\n", 1);
}
