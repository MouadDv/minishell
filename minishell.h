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
	char    *cmd;
    char    **args;
    struct s_red   *redirections;
	struct s_cmd   *next;
}				t_cmd;

typedef struct s_red
{
	char    type;
    char    *arg;
	struct s_red   *next;
}				t_red;

typedef struct s_node {
    char    *name;
    char    *val;
    struct s_node *next;
} t_node;


int     scan(char *str);
int    parse_and_exec(char *buf, t_node	*node);
t_cmd   *alloc_cmd_s();
t_red   *alloc_red_s();
int     end_of_delimiter(char *str);
void    subarg(int   *r, int i, char *str, t_red *red);
int     sizelen(char    *str, int   ret, int    i);
char    **splitargs(char    *str);
int     data_proc(t_cmd   *strct, t_node	*node);
char    *env_val(char   *name, t_node	*node);




char	*ft_strjoin1(char const *s1, char const *s2);
void	*ft_memcpy1(void *dest, const void *src, size_t n);


#endif