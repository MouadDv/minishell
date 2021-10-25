#include "minishell.h"



void	call_exec(t_cmd *strct, t_node *head)
{
	t_node *temp;
	t_cmd *tmp;

	tmp = strct;
	temp = head;
	printf("execve\n");
}
void ft_builtins(t_cmd *strct, t_node *node, int *flag)
{
	t_node *temp;
	t_cmd *tmp;
	int i;

	i = 0;
	tmp = strct;
	temp = node;
	if (ft_strncmp(tmp->args[0], "cd", 2) == 0)
		impli_cd(tmp->args[1], node);
	else if (ft_strncmp(tmp->args[0], "export", 6) == 0)
	{
		printf("export\n");
	}
	else if (ft_strncmp(tmp->args[0], "unset", 5) == 0)
		printf("unset\n");
	else if (ft_strncmp(tmp->args[0], "env", 3) == 0)
		printf("env\n");
	else if (ft_strncmp(tmp->args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tmp->args[0], "echo", 4) == 0)
		printf("echo\n");
	else if (ft_strncmp(tmp->args[0], "exit", 4) == 0)
		printf("exit\n");
	else
		*flag = 1;
}



void	ft_simple_cmd(t_cmd *strct, t_node *node)
{
	int flag;

	flag = 0;
	ft_builtins(strct, node , &flag);
	if (flag == 1)
		call_exec(strct, node);

}


void 	ft_execution(t_cmd *strct, t_node *node)
{
	t_cmd   *tmp;

	tmp = strct;

	if (tmp->next != NULL)
		printf("bzff d les commandes\n");
	else
		ft_simple_cmd(strct, node);
}