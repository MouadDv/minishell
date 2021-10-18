#include "minishell.h"

t_cmd   *alloc_cmd_s()
{
    t_cmd   *ret;

    ret = malloc(sizeof(t_cmd));
    if (!ret)
        return (0);
    ret->args = NULL;
    ret->cmd = NULL;
    ret->next = NULL;
    ret->redirections = NULL;
    return (ret);
}

t_red   *alloc_red_s()
{
    t_red   *ret;

    ret = malloc(sizeof(t_red));
    if (!ret)
        return (0);
    ret->arg = NULL;
    ret->next = NULL;
    ret->type = 0;
    return (ret);
}

int     end_of_delimiter(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i] != ' ')
        i++;
    return (i);
}

void    subarg(int   *r, int i, char *str, t_red *red)
{
    while (str[i] == ' ' && str[i])
            i++;
    red->arg = ft_substr(str, i, end_of_delimiter(str + i));
    *r = *r + i - 1;
}

void    get_command(char    *str, int   *r, t_cmd *cmd, int i)
{
    int e;

    e = i + 1;
    if (str[i] == '"')
    {
        while (str[e] && str[e] != '"')
            e++;
        cmd = ft_substr(str, i, e);
    }
    else
    {
        while (str[e] && str[e] != '|' && str[e] != '<' && str[e] != '>')
            e++;
        cmd = ft_substr(str, i, e);
    }
}