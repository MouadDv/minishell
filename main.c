/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:15:01 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/24 07:31:35 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_data.statuscode = 1;
		rl_on_new_line();
		write (1, "\033[32;1mminishell$ \033[0m", 23);
		write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
		write (1, "  \b\b\n", 5);
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	get_line(t_node *node)
{
	char	*buf;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	buf = readline("\033[32;1mminishell$ \033[0m");
	if (buf == NULL)
	{
		write(1, "exit\n", 5);
		free_node(node);
		free(g_data.tab);
		exit(0);
	}
	if (ft_strlen(buf) > 0)
	{
		add_history(buf);
		if (scan(buf) == 0)
		{
			g_data.statuscode = 258;
			write (1, "Minishell: Syntax error\n", 24);
		}
		else
			parse_and_exec(buf, node);
	}
	free(buf);
}

void	ft_init()
{
	g_data.newpath = NULL;
	g_data.cmderr = NULL;
	g_data.tab = malloc(sizeof(int) * 3);
	if (!g_data.tab)
		protection();
}

int	main(int argc, char **argv, char **env)
{
	t_node	*node;
	char	**newenv;
	int		i;

	node = NULL;
	i = 0;
	if (argc == 1)
	{
		g_data.statuscode = 0;
		ft_strlen(argv[0]);
		newenv = copy_env(env);
		init_struct(newenv, &node);
		g_data.node = node;
		ft_init();
		while (newenv[i++])
			free_null(newenv[i - 1]);
		free_null(newenv);
		while (1)
			get_line(node);
		return (0);
	}
	return (1);
}

char	*get_name(char	*str)
{
	char	*ret;
	int		i;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}
