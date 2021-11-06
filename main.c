#include "minishell.h"

void    sighandler(int  sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        write (1, "\033[35;1mminishell$ \033[0m", 23);
        write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
        write (1, "  \b\b\n", 5);
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

char **copy_env(char **env)
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


char *get_line(t_node *node)
{
    char    *buf;

    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sighandler);
    buf = readline("\033[35;1mminishell$ \033[0m");
    if (buf == NULL)
    {
        write(1, "exit\n", 5);
        exit(0);
    }
    if (ft_strlen(buf) > 0) {
        add_history(buf);
    }
    // write (1, buf, ft_strlen(buf));
    // write (1, "\n", 1);
    if (scan(buf) == 0)
        write (1, "Minishell: Syntax error\n", 24);
    else
        parse_data(buf, node);
    free(buf);
    return (buf);
}

int main(int argc, char **argv, char **env)
{
	t_node	*node;
	char **newenv;
   // g_data.statuscode = 0;

    node = NULL;
    if (argc == 1)
    {
        ft_strlen(argv[0]);
        newenv = copy_env(env);
        init_struct(newenv, &node);
        signal(SIGQUIT, SIG_IGN);
        while (1)
        {
            signal(SIGINT, sighandler);
           	get_line(node);		   
        }
        return 0;
    }
    return 1;
}