/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_norm2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:03:42 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/25 01:46:24 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_norm_pipes(t_cmd	*tmp, t_red	*tmp2, t_node *node)
{
	while (tmp)
	{
		tmp2 = tmp->redirections;
		pipe(g_data.p);
		g_data.pid = fork();
		if (!tmp2 || !ft_search(tmp2, 'h'))
		{
			g_data.tab_pids[g_data.i] = g_data.pid;
			g_data.i++;
		}
		if (g_data.pid == -1)
			exit (EXIT_FAILURE);
		else if (g_data.pid == 0)
			ft_child_pipe(tmp, tmp2, node, g_data.j);
		else
		{
			if (tmp2 && ft_search(tmp2, 'h'))
				waitpid(g_data.pid, &g_data.statuscode, 0);
			ft_save_input_for_next_cmd();
		}
		tmp = tmp->next;
		g_data.j++;
	}
}
