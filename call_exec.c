/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:52 by chicky            #+#    #+#             */
/*   Updated: 2021/11/05 20:21:05 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_absolute_path(char **cmd, int *j)
{
	char	*newpath;

	newpath = ft_strdup(*cmd);
	*j = 0;
	if (access(newpath, F_OK) == 0)
	{
		if (open(newpath, O_DIRECTORY) > 0)
		{
			*j = 1;
			return (newpath);
		}
		else if (access(newpath, R_OK | X_OK) == 0)
		{
			*j = 0;
			return (newpath);
		}
	}
	free(newpath);
	return (NULL);
}

char	*ft_check_absolute_path(char **cmd)
{
	int	flag;
	char *newpath;

	newpath = if_absolute_path(cmd, &flag);
	if (flag == 1)
	{
		write(2, newpath, ft_strlen(newpath));
		free(newpath);
		write(2, ": Is a Directory\n", 17);
		g_data.statuscode = 126;
		newpath = NULL;
	}
	else if (newpath == NULL)
	{
		write(2, "invalid cmd\n", 12);
		g_data.statuscode = 127;
	}
	return (newpath);
}

char 	**ft_find_path(char **path, char **ptrs)
{
	char *newpath;

	if (ptrs[0] == NULL)
	{
		write(2, "invalid cmd\n", 12);
		g_data.statuscode = 127;
	}
	else if (ft_strncmp(ptrs[0], "/", 1) == 0)
		newpath = ft_check_absolute_path(ptrs);
	else
	{
		newpath = ft_check_path(path, ptrs);
		if (newpath == NULL)
		{
			write(2, "invalid cmd\n", 12);
			g_data.statuscode = 127;
		}
	}
	ptrs[0] = newpath;
	return (ptrs);
}

char	**ft_path(t_node *head)
{
	t_node *cur;
	char *value;
	char *ret;
	char **ptr;
	cur = head;

	while (cur != NULL)
	{
		if (ft_strncmp(cur->name, "PATH", ft_strlen(cur->name)) == 0)
		{
			value = cur->val;
			ret = ft_substr(value, 2, (ft_strlen(value) - 3));
			ptr = ft_split(ret, ':');
		} 
		cur = cur->next;
	}
	return (ptr);
}

char	*ft_if_exec(char **path, char *file, int *j)
{
	char	*newpath;

	newpath = ft_strjoin(path[*j], file);
	if (access(newpath, F_OK) == 0)
	{
		if (access(newpath, R_OK | X_OK) == 0)
		{
			free(file);
			return (newpath);
		}
		else
		{
			free(file);
			free(newpath);
			return (NULL);
		}	
	}
	free(newpath);
	return (NULL);
}

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


void	call_exec(char **cmd, t_node *head)
{
	char	**path;
	int		i;
	pid_t	p;
	
	i = 0;
	path = ft_path(head);
	cmd = ft_find_path(path, cmd);
	p = fork();
	if (p == -1)
		exit (EXIT_FAILURE);
	else if (p == 0)
	{
		execve(cmd[0], cmd, NULL);
	 	exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}