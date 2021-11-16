/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:41 by milmi             #+#    #+#             */
/*   Updated: 2021/11/16 20:22:33 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void	*buff)
{
	if (buff != NULL)
		free(buff);
	buff = NULL;
}

void	free_strct(t_cmd	*strct, t_red	*tmp, t_red	*tmp2, t_cmd	*tmp3)
{
	int	i;

	while (strct)
	{
		tmp3 = strct;
		tmp2 = strct->redirections;
		i = 0;
		free(strct->cmd);
		while (strct->args[i])
		{
			free_null(strct->args[i]);
			i++;
		}
		free_null(strct->args);
		while (tmp2)
		{
			tmp = tmp2;
			free_null(tmp2->arg);
			tmp2 = tmp2->next;
			free(tmp);
		}
		strct = strct->next;
		free(tmp3);
	}
}

void	free_node(t_node	*node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node;
		free_null(node->name);
		free_null(node->val);
		node = node->next;
		free_null(tmp);
	}
}

void	protection(void)
{
	free_strct(g_data.strct, NULL, NULL, NULL);
	free_node(g_data.node);
	exit(1);
}

void	print_invalid_cmd(char *cmd)
{
	write(2, "bash: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	g_data.statuscode = 127;
}
