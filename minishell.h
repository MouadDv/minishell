#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <limits.h>
#include <sys/param.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
# include <signal.h>

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

typedef struct s_data {
	
	int statuscode;
	int	saved[2];
	
}	t_data;

t_data g_data;


int		scan(char *str);
int		parse_data(char *buf, t_node *node);
t_cmd	*alloc_cmd_s();
t_red	*alloc_red_s();
int		end_of_delimiter(char *str);
void	subarg(int   *r, int i, char *str, t_red *red);
int		sizelen(char    *str);
char	**splitargs(char    *str);
/* execution */
void 	ft_execution(t_cmd   *strct, t_node *node);
void	impli_cd(char *ptr, t_node *node);
void 	ft_pwd(void);
void    ft_global_export(char **ptr, t_node	*node);
t_node	*copy_list(t_node *node);
void 	ft_sort_list(t_node *head);
void  	ft_export(t_node *head);
int 	ft_check(t_node **head,char *name, char *val, int *flag);
int 	ft_check_valid_identifier(char *name);
void 	test_add(t_node **head, char *name, char *val);
void	init_struct(char **envp, t_node **head);
void 	ft_unset(t_node **head, char *name);
void 	ft_env(t_node *head);
void 	ft_global_echo(char **ptr);
int 	ft_echo_utils(char **ptr, int *opt);
void 	ft_echo(char **ptr, int m, int *opt);
void	ft_exit(char **ptr);
void	call_exec(char **cmd, t_node *head);
char	**ft_path(t_node *head);
char 	**ft_find_path(char **path, char **ptrs);
char	*if_absolute_path(char **cmd, int *j);
char	*ft_check_absolute_path(char **cmd);
char	*ft_if_exec(char **path, char *file, int *j);
char	*ft_check_path(char **path, char **cmd);
void	ft_pipes(t_node *node, t_cmd *strct);
void 	ft_exec_child_redir(char **cmd, t_red *redir, t_node *head);
void 	ft_exec_child_heredoc(char **cmd, t_red *redir, t_node *head);
void 	ft_builtins(char **ptr, t_node *node, int *flag);


char	*ft_strjoin1(char const *s1, char const *s2);
void	*ft_memcpy1(void *dest, const void *src, size_t n);


#endif