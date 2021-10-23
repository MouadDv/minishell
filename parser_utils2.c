#include "minishell.h"

int     sizelen(char    *str)
{
    int     ret;
    int     i;

    ret = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            ret++;
            while (str[i + 1] && !(str[i + 1] == '"' && (str[i + 2] == ' ' || str[i + 2] == '\0')))
                i++;
        }
        else if (str[i] == '\'')
        {
            ret++;
            while (str[i + 1] && !(str[i + 1] == '\'' && (str[i + 2] == ' ' || str[i + 2] == '\0')))
                i++;
        }
        else if (str[i] != ' ')
        {
            ret++;
            while (str[i + 1] && str[i + 1] != ' ')
                i++;
        } 
        i++;
    }
    return (ret);
}

char    *get_arg(char   *str, int   *r)
{
    int     i;
    char    *ret;
    int     s;

    i = *r;
    s = 0;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '"')
    {
        while (str[s] && !(str[s] == '"' && (str[s + 1] == ' ' || str[s + 1] == '\0')))
            s++;
        ret = ft_substr(str + i, 0, s);
    }
    else if (str[i] == '\'')
    {
        while (str[s] && !(str[s] == '\'' && (str[s + 1] == ' ' || str[s + 1] == '\0')))
            s++;
        ret = ft_substr(str + i, 0, s);
    }
    else
    {
        while (str[s] && str[s] != ' ')
            s++;
        ret = ft_substr(str + i, 0, s);
    }
    *r = i + s;
    return (ret);
}

char    **splitargs(char    *str)
{
    char    **ret;
    int     size;
    int     i;
    int     r;

    size = sizelen(str);
    ret = malloc(sizeof(char *) * (size + 1));
    if (!ret)
        return (NULL);
    i = 0;
    r = 0;
    while (i < size)
    {
        ret[i] = get_arg(str, &r);
        i++;
    }
    ret[size] = NULL;
    return (ret);
}