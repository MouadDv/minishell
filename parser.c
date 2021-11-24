/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:50 by milmi             #+#    #+#             */
/*   Updated: 2021/11/24 04:17:15 by milmi            ###   ########.fr       */
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

void	add_to_args(t_cmd *strct, char *str, int size, int size2)
{
	char	**tmp;
	char	**ret;

	size = sizeoftab(strct->args);
	tmp = splitargs(str);
	size2 = sizeoftab(tmp);
	ret = malloc((size + size2 + 1) * sizeof(char *));
	if (ret == NULL)
		protection();
	ret[size + size2] = NULL;
	size = 0;
	size2 = 0;
	while (strct->args[size] != NULL)
	{
		ret[size] = strct->args[size];
		size++;
	}
	while (tmp[size2] != NULL)
	{
		ret[size + size2] = tmp[size2];
		size2++;
	}
	free(strct->args);
	strct->args = ret;
	free(tmp);
}

void	get_cmd(char *s, t_cmd *strct, int *r, int i)
{
	int		f;
	char	c;

	f = 0;
	if (s[i] != '<' && s[i] != '>' && s[i] != '|')
	{
		while ((s[i] && s[i] != '<' && s[i] != '>' && s[i] != '|') || f == 1)
		{
			get_cmd_norm(s, i, &f, &c);
			i++;
		}
		if (strct->cmd != NULL)
			free(strct->cmd);
		strct->cmd = ft_substr(s, 0, i);
		*r = *r + i - 1;
	}
	if (strct->args == NULL)
		strct->args = splitargs(strct->cmd);
	else
		add_to_args(strct, strct->cmd, 0, 0);
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
		else if (!ft_isspace(str[i]))
			get_cmd(str + i, strct, &i, 0);
		i++;
	}
}

int	parse_and_exec(char *buf, t_node *node)
{
	char	*str;
	t_cmd	*strct;

	strct = alloc_cmd_s();
	g_data.strct = strct;
	if (!strct)
		return (0);
	str = ft_strtrim(buf, " \t\n\v\f\r");
	parce_syntax(str, strct, NULL, 0);
	data_proc(strct, node);
	rm_quotes(strct);
	g_data.statuscode = 0;
	g_data.thereishd = 0;
	ft_count_nbrcmd(strct);
	g_data.tab_pids = malloc(sizeof(pid_t) * g_data.nbr_cmd + 1);
	ft_execution(strct, node);
	free_strct(strct, NULL, NULL, NULL);
	free_null(str);
	free_null(g_data.tab_pids);
	return (1);
}
