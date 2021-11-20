/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_norm3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:48:26 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/19 18:48:47 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_var_input(t_red *tmp2, int *var)
{
	g_data.fdin = ft_ret_input_fd(tmp2);
	if (g_data.fdin < 0)
		*var = 1;
}

void	ft_check_var_output(t_red *tmp2, int *var)
{
	g_data.fdout = ft_ret_outputfd(tmp2);
	if (g_data.fdout < 0)
		*var = 1;
}

void	ft_check_var_append(t_red *tmp2, int *var)
{
	g_data.fdout = ft_ret_appendfd(tmp2);
	if (g_data.fdout < 0)
		*var = 1;
}
