/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:34:40 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/09 20:07:39 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_b_in_export_norm(char **ptr, t_node *node)
{
	t_node	*temp;
	g_data.statuscode = 0;

	if (ptr[1])
		ft_global_export(ptr, node);
	else
	{
		temp = copy_list(node);
		ft_sort_list(temp);
		ft_export(temp);
	}
}

void	ft_b_in_echo_norm(char **ptr)
{
	if (ptr[1])
	{
		if (ft_strncmp(ptr[1], "$?", ft_strlen(ptr[1])) == 0)
		{
			printf("%d\n", g_data.statuscode);
			g_data.statuscode = 0;
		}
		else
			ft_global_echo(ptr);
	}
	else
		write(1, "\n", 1);
}

void	ft_builtins(char **ptr, t_node *node, int *flag)
{
	if (ft_strncmp(ptr[0], "cd", ft_strlen(ptr[0])) == 0)
		impli_cd(ptr[1], node);
	else if (ft_strncmp(ptr[0], "export", ft_strlen(ptr[0])) == 0)
		ft_b_in_export_norm(ptr, node);
	else if (ft_strncmp(ptr[0], "unset", ft_strlen(ptr[0])) == 0)
	{
		ft_unset_global(&node ,ptr);
	}
	else if (ft_strncmp(ptr[0], "env", ft_strlen(ptr[0])) == 0)
		ft_env(node);
	else if (ft_strncmp(ptr[0], "pwd", ft_strlen(ptr[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(ptr[0], "echo", ft_strlen(ptr[0])) == 0)
		ft_b_in_echo_norm(ptr);
	else if (ft_strncmp(ptr[0], "exit", ft_strlen(ptr[0])) == 0)
		ft_exit(ptr);
	else
		*flag = 1;
}

void	ft_simple_cmd(t_cmd *strct, t_node *node)
{
	int		flag;
	t_cmd	*tmp;

	flag = 0;
	tmp = strct;
	ft_builtins(tmp->args, node, &flag);
	if (flag == 1)
		call_exec(tmp->args);
}

void	ft_execution(t_cmd *strct, t_node *node)
{
	t_cmd	*tmp;
	t_red	*tmp2;

	tmp = strct;
	tmp2 = tmp->redirections;
	if (tmp->next != NULL)
		ft_pipes(node, strct);
	else if (tmp2)
		ft_global_redir(strct, node);
	else
		ft_simple_cmd(strct, node);
}
