/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_strct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:36 by milmi             #+#    #+#             */
/*   Updated: 2021/11/16 08:51:31 by milmi            ###   ########.fr       */
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

void	test_add(t_node	**head, char	*name, char	*val)
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

char	**env_gen(t_node *node)
{
	char	**ret;
	char	*sub;
	char	*equal;
	int		i;
	t_node	*tmp;

	tmp = node;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ret = malloc((i + 1) * sizeof(char *));
	if (!ret)
		protection();
	ret[i] = NULL;
	tmp = node;
	i = 0;
	while (tmp)
	{
		sub = ft_substr(tmp->val, 2, ft_strlen(tmp->val - 3));
		equal = ft_strjoin("=", sub);
		ret[i] = ft_strjoin(tmp->name, equal);
		free (sub);
		free (equal);
		tmp = tmp->next;
	}
	return (ret);
}
