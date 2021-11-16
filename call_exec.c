/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:52 by chicky            #+#    #+#             */
/*   Updated: 2021/11/16 21:40:29 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_path(char **path, char **cmd)
{
	int		j;
	char	*newpath;
	char	*file;

	j = 0;
	file = ft_strjoin("/", *cmd);
	while (path[j] != NULL)
	{
		newpath = ft_if_exec(path, file, &j);
		if (newpath)
			return (newpath);
		j++;
	}
	free(file);
	return (NULL);
}

void	call_exec(char **cmd)
{
	pid_t	p;
	char	**envp;

	g_data.ptrs = ft_find_path(g_data.path, cmd);
	envp = env_gen(g_data.node);
	p = fork();
	if (p == -1)
		exit (EXIT_FAILURE);
	else if (p == 0)
	{
		execve(g_data.ptrs[0], g_data.ptrs, envp);
		exit(g_data.statuscode);
	}
	else
		waitpid(p, &g_data.statuscode, 0);
	g_data.statuscode = WEXITSTATUS(g_data.statuscode);
}
