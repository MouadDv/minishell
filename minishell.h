#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <unistd.h>
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
    char    *filename;
    char    *delimiter;
	struct os_red   *next;
}				t_red;

int    scan(char *str);

#endif