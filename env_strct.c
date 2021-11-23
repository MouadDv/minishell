/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_strct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:36 by milmi             #+#    #+#             */
/*   Updated: 2021/11/23 12:34:27 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char	**env)
{
	char	**newenv;
	int		l;
	int		i;

	i = 0;
	l = 0;
	while (env[l])
		l++;
	newenv = malloc(sizeof(char *) * (l + 1));
	if (newenv == NULL)
		return (NULL);
	newenv[l] = NULL;
	while (env[i])
	{
		newenv[i] = ft_strdup(env[i]);
		if (newenv[i] == NULL)
			return (NULL);
		i++;
	}
	return (newenv);
}

void	test_add(t_node	**head, char *name, char	*val)
{
	t_node	*newnode;
	t_node	*lastnode;

	newnode = malloc(sizeof(t_node));
	newnode->name = ft_strdup(name);
	newnode->val = ft_strdup(val);
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		lastnode = *head;
		while (lastnode->next != NULL)
			lastnode = lastnode->next;
		lastnode->next = newnode;
	}
}

void	init_struct(char	**envp, t_node	**head)
{
	int		i;
	char	*s;
	char	*key;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		s = ft_strchr(envp[i], '=');
		if (s)
		{
			*s = '\0';
			key = ft_strjoin("=\"", (s + 1));
			tmp = key;
			key = ft_strjoin(key, "\"");
			free_null(tmp);
			test_add(head, envp[i], key);
			free_null(key);
		}
		i++;
	}
}

void	env_gen_norm(t_node	*tmp)
{
	char	*tmp2;
	int		i;

	i = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->val) == 0)
			g_data.sub = ft_strdup("");
		else
			g_data.sub = ft_substr(tmp->val, 2, (ft_strlen(tmp->val) - 3));
		tmp2 = g_data.sub;
		if (ft_strlen(g_data.sub) != 0)
		{
			g_data.sub = ft_strjoin("=", g_data.sub);
			g_data.ret[i] = ft_strjoin(tmp->name, g_data.sub);
			free_null(g_data.sub);
		}
		else
			g_data.ret[i] = ft_strdup(tmp->name);
		free_null(tmp2);
		tmp = tmp->next;
		i++;
	}	
}

char	**env_gen(t_node *node)
{
	int		len;
	t_node	*tmp;

	tmp = node;
	len = len_list(node);
	g_data.ret = malloc((len + 1) * sizeof(char *));
	if (!g_data.ret)
		protection();
	g_data.ret[len] = NULL;
	tmp = node;
	env_gen_norm(tmp);
	return (g_data.ret);
}
