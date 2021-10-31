#include "minishell.h"

void    sighandler(int  sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        write (1, "minishell>> ", 12);
        write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
        write (1, "  \b\b\n", 5);
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

char    **copy_env(char **env)
{
	char **newenv;
	int l;
	int i;
	
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

void    test_add(t_node **head, char *name, char *val)
{
    t_node  *newnode;
    t_node  *lastnode;

    newnode = malloc(sizeof(t_node));
    newnode->name = ft_strdup(name);
    newnode->val = ft_strdup(val);
    newnode->next = NULL;
    if(*head == NULL)
         *head = newnode;
    else
    {
        lastnode = *head;
        while(lastnode->next != NULL)
            lastnode = lastnode->next;
        lastnode->next = newnode;
    }

}

void	init_struct(char **envp, t_node **head)
{
    int     i;
    char    *s;
    char    *key;
    char    *tmp;

    i = 0;
  
    while (envp[i])
    {
        if((s = ft_strchr(envp[i], '=')))
        {
            *s = '\0';
            key = ft_strjoin1("=\"", (s+1));
            tmp = key;
            key = ft_strjoin1(key, "\"");
            free_null(tmp);
            test_add(head, envp[i], key);
            free_null(key);
        }
        i++;
    }
}

void    get_line(t_node	*node)
{
    char    *buf;

    buf = readline("minishell>> ");
    if (buf == NULL)
    {
        write(1, "exit\n", 5);
        free_node(node);
        exit(0);
    }
    if (ft_strlen(buf) > 0) {
        add_history(buf);

        if (scan(buf) == 0)
            write (1, "Minishell: Syntax error\n", 24);
        else
            parse_and_exec(buf, node);
    }
    free(buf);
}

int     main(int argc, char **argv, char **env)
{
	t_node	*node;
	char **newenv;
    int     i;

    node = NULL;
    i = 0;
    if (argc == 1)
    {
        ft_strlen(argv[0]);
        newenv = copy_env(env);
        init_struct(newenv, &node);
        while (newenv[i++])
            free_null(newenv[i - 1]);
        free_null(newenv);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, sighandler);
        while (1)
            get_line(node);
        return 0;
    }
    return 1;
}
