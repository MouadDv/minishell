/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:05:59 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/24 04:50:41 by sbensarg         ###   ########.fr       */
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

	g_data.newpath = if_absolute_path(cmd, &flag);
	if (flag == 1)
	{
		write(2, g_data.newpath, ft_strlen(g_data.newpath));
		free(g_data.newpath);
		write(2, ": Is a Directory\n", 17);
		g_data.statuscode = 126;
		g_data.newpath = NULL;
	}
	else if (g_data.newpath == NULL)
		print_invalid_cmd(cmd[0]);
	return (g_data.newpath);
}

char	**ft_find_path(char **path, char **ptrs)
{
	// if (g_data.newpath != NULL)
	// 	free (g_data.newpath);
	if (ptrs[0][0] == '\0')
	{
		write(2, "bash: ", 7);
		write(2, ": command not found\n", 21);
		g_data.statuscode = 127;
	}
	else if (ft_strncmp(ptrs[0], "/", 1) == 0
		|| ft_strncmp(ptrs[0], ".", 1) == 0)
		g_data.newpath = ft_check_absolute_path(ptrs);
	else
	{
		g_data.newpath = ft_check_path(path, ptrs);
		if (g_data.newpath == NULL)
			print_invalid_cmd(ptrs[0]);
	}
	if (ptrs[0][0] != '\0' && g_data.newpath != NULL)
	{
		free(ptrs[0]);
		ptrs[0] = ft_strdup(g_data.newpath);
	}
	return (ptrs);
}

char	**ft_path(t_node *head)
{
	t_node	*cur;
	char	*value;
	char	*ret;
	char	**ptr;
	char	*tmp;

	cur = head;
	ptr = NULL;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->name, "PATH", ft_strlen(cur->name)) == 0)
		{
			value = cur->val;
			ret = ft_substr(value, 2, (ft_strlen(value) - 3));
			tmp = ret;
			ptr = ft_split(ret, ':');
			free (ret);
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
