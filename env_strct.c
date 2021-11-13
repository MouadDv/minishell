/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_strct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:34:36 by milmi             #+#    #+#             */
/*   Updated: 2021/11/12 04:34:38 by milmi            ###   ########.fr       */
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
