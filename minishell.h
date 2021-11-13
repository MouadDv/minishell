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
#include <sys/wait.h>

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
	
	int		statuscode;
	int		saved[2];
	char	*cmderr;
	int		flagerr;
	char	*newpath;
	char	**path;
	int  	fd_in;
	int		fd_old;
	int		fd[2];
	int		p[2];
	pid_t	pid;
	int		*tab;
	char	**ptrs;
	pid_t	p1;
	int		fdin;
	int		fdout;
	char	*wrd;
    char	*val;

	
}	t_data;

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

t_data g_data;


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
void 	ft_unset_global(t_node **head, char **ptr);
void 	ft_env(t_node *head);
void 	ft_global_echo(char **ptr);
int 	ft_echo_utils(char **ptr, int *opt);
void 	ft_echo(char **ptr, int m, int *opt);
void	ft_exit(char **ptr);
void	call_exec(char **cmd);
char	**ft_path(t_node *head);
char 	**ft_find_path(char **path, char **ptrs);
char	*if_absolute_path(char **cmd, int *j);
char	*ft_check_absolute_path(char **cmd);
char	*ft_if_exec(char **path, char *file, int *j);
char	*ft_check_path(char **path, char **cmd);
void	ft_pipes(t_node *node, t_cmd *strct);
void 	ft_exec_redir(char **cmd, t_cmd *strct, t_node *head);
void 	ft_builtins(char **ptr, t_node *node, int *flag);
void 	ft_global_redir(t_cmd *strct, t_node *head);
int		*ft_tab_of_in_out(t_red *redir);
int 	ft_heredoc(t_red *redir);
void	ft_exec_redirections(char **cmd, t_red *redir, t_node *node);
void	ft_dup_redir_in_pipes(t_red	*redir);
void	ft_check_err_piped_redir(void);
void	ft_check_err_redir(void);

int		ft_ret_input_fd(t_red *tmp2);
int		ft_ret_heredoc_fd(t_red *tmp2);
int		ft_ret_outputfd(t_red *tmp2);
int		ft_ret_appendfd(t_red *tmp2);
void	ft_tab_of_in_out_norm(t_red *tmp2);
void	reset_dup(void);
void 	ft_check_err_norm(void);
void	ft_check_err_norm2(t_red *tmp2);
void	ft_global_check_err_norm(void);
void	ft_print_err_msg(char *msg);

void 	ft_sort_list(t_node *head);
t_node	*copy_list(t_node *node);
int 	ft_check_valid_identifier(char *name);
int 	ft_check(t_node **head,char *name, char *val, int *flag);
void 	test_add(t_node **head, char *name, char *val);
int 	len_list(t_node *head);
void	ft_swap(t_node *tmp1, t_node *tmp2);
void	ft_sort_list(t_node *head);
t_node	*alloc_list(void);
t_node	*copy_list(t_node *node);
int		ft_check_valid_identifier(char *name);


#endif