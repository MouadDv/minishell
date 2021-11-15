/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milmi <milmi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 04:33:21 by milmi             #+#    #+#             */
/*   Updated: 2021/11/15 03:50:08 by milmi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_red	*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_red
{
	char			type;
	char			*arg;
	struct s_red	*next;
}	t_red;

typedef struct s_node {
	char			*name;
	char			*val;
	struct s_node	*next;
}	t_node;

typedef struct {
	int		i;
	char	*ret;
	char	*name;
	char	*val;
	char	*val2;
}	s_rp;

typedef struct s_fr {
	void		*name;
	struct s_fr	*next;
}	t_fr;

int		scan(char *str);
int		parse_and_exec(char *buf, t_node	*node);
t_cmd	*alloc_cmd_s(void);
t_red	*alloc_red_s(void);
int		end_of_delimiter(char *str);
void	subarg(int	*r, int i, char *str, t_red *red);
int		sizelen(char	*str, int	ret, int	i, int	trig);
char	**splitargs(char	*str);
void	data_proc(t_cmd	*strct, t_node	*node);
char	*env_val(char	*name, t_node	*node);
void	free_null(void	*buff);
void	free_strct(t_cmd	*strct, t_red	*tmp, t_red	*tmp2, t_cmd	*tmp3);
void	free_node(t_node	*node);
char	*get_arg(char	*str, int	*r);
char	**copy_env(char	**env);
void	test_add(t_node	**head, char	*name, char	*val);
void	init_struct(char	**envp, t_node	**head);
char	*ft_strjoin1(char	*s1, char const	*s2);
void	*ft_memcpy1(void *dest, const void *src, size_t n);
char	*get_name(char	*str);
void	print_strct(t_cmd	*strct);
void	rm_quotes(t_cmd *srtct);
void	protection(t_cmd *node);
int		sizeoftab(char	**tab);

#endif
