/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:50 by milmi             #+#    #+#             */
/*   Updated: 2021/11/15 19:12:31 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redir(char *str, t_red *red, int *r)
{
	if (str[0] == '<' && str[1] == '<')
	{
		red->type = 'h';
		subarg(r, 2, str, red);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		red->type = 'a';
		subarg(r, 2, str, red);
	}
	else if (str[0] == '>')
	{
		red->type = 'o';
		subarg(r, 1, str, red);
	}
	else if (str[0] == '<')
	{
		red->type = 'i';
		subarg(r, 1, str, red);
	}
}

void	get_cmd(char *str, t_cmd *strct, int *r)
{
	int	i;

	i = 0;
	if (str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
			i++;
		strct->cmd = ft_substr(str, 0, i);
		*r = *r + i - 1;
	}
	strct->args = splitargs(strct->cmd);
}

void	parce_syntax(char *str, t_cmd *strct, t_red *tmp, int i)
{
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (strct->redirections == NULL)
			{
				strct->redirections = alloc_red_s();
				tmp = strct->redirections;
			}
			else
			{
				tmp->next = alloc_red_s();
				tmp = tmp->next;
			}
			get_redir(str + i, tmp, &i);
		}
		else if (str[i] == '|')
		{
			strct->next = alloc_cmd_s();
			strct = strct->next;
		}
		else if (str[i] != ' ')
			get_cmd(str + i, strct, &i);
		i++;
	}
}

void	free_ptrs(char **ptrs)
{
	int i;

	i = 0;
	while (ptrs[i])
	{
		free(ptrs[i]);
		i++;
	}
	free(ptrs);
}

int	parse_and_exec(char *buf, t_node *node)
{
	char	*str;
	t_cmd	*strct;

	strct = alloc_cmd_s();
	if (!strct)
		return (0);
	str = ft_strtrim(buf, " ");
	parce_syntax(str, strct, NULL, 0);
	data_proc(strct, node);
	rm_quotes(strct);
	ft_execution(strct, node);
	//print_strct(strct);
	free_strct(strct, NULL, NULL, NULL);
	free_null(str);
	return (1);
}
