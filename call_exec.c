/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:06:52 by chicky            #+#    #+#             */
/*   Updated: 2021/11/24 06:54:01 by milmi            ###   ########.fr       */
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
	while (path && path[j] != NULL)
	{
		newpath = ft_if_exec(path, file, &j);
		if (newpath)
			return (newpath);
		j++;
	}
	free(file);
	return (NULL);
}

void	signalhandling(void)
{
	if (WIFSIGNALED(g_data.statuscode))
	{
		g_data.statuscode = WTERMSIG(g_data.statuscode) + 128;
		if (WTERMSIG(g_data.statuscode) == SIGQUIT)
			write(2, "Quit: 3\n", 8);
		else if (WTERMSIG(g_data.statuscode) == SIGINT)
			write(2, "\n", 1);
	}
	else
		g_data.statuscode = WEXITSTATUS(g_data.statuscode);
}

void	call_exec(char **cmd)
{
	pid_t	p;
	char	**envp;

	g_data.path = ft_path(g_data.node);
	g_data.ptrs = ft_find_path(g_data.path, cmd);
	envp = env_gen(g_data.node);
	p = fork();
	if (p == -1)
		exit (EXIT_FAILURE);
	else if (p == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(g_data.ptrs[0], g_data.ptrs, envp);
		exit(g_data.statuscode);
	}
	else
		waitpid(p, &g_data.statuscode, 0);
	signalhandling();
	free_envp(envp);
}

void	print_invalid_cmd(char *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	g_data.statuscode = 127;
}

void	ft_err_export(char *name, char *value)
{
	write(2, "bash: export: « ", 17);
	write(2, name, ft_strlen(name));
	if (value != NULL)
		write(2, value, ft_strlen(value));
	write(2, " » : identifiant non valable\n", 30);
	g_data.statuscode = 1;
}
