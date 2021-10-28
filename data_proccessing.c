#include "minishell.h"

char    *get_name(char  *str)
{
    char    *ret;
    int     i;

    i = 1;
    while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != ' ')
        i++;
    ret = ft_substr(str, 1, i - 1);
    return (ret);
}

void    replace_env(char    **str, t_node	*node)
{
    char    *locat;
    char    *name;

    locat = ft_strchr(*str, '$');
    while (locat != NULL)
    {
        if (*(locat + 1) != '"' &&  *(locat + 1) != '$' && *(locat + 1) != '\0' && *(locat + 1) != ' ')
        {
            printf("{%s}\n", locat);
            name = get_name(locat);
            printf("[%s] = %s\n", name, env_val(name, node));
        }
        locat = ft_strchr(locat + 1, '$');   
    }
    
}

int     data_proc(t_cmd   *strct, t_node	*node)
{
    strct = NULL;
    char    *str;

    str = strdup("echo $HOME $PATH dsfk \"$HOME\"");
    replace_env(&str, node);
    return (1);
}