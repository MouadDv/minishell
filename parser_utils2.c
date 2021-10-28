#include "minishell.h"

void    sizelen_norm(int    *i, int    *ret, char   *str)
{
    int     trig;

    if (str[*i] == '\'')
    {
        *ret = *ret + 1;
        *i = *i + 1;
        trig = 1;
        while (str[*i])
        {
            if (str[*i] == '\'' && trig == 0)
                trig = 1;
            else if (str[*i] == '\'')
                trig = 0;
            if (str[*i] == ' ' && trig == 0)
                break;
             *i = *i + 1;
        }
    }
    else if (str[*i] != ' ')
    {
        *ret = *ret + 1;
        while (str[*i] && str[*i] != ' ')
             *i = *i + 1;
    }
}

int     sizelen(char    *str, int   ret, int    i)
{
    int     trig;

    while (str[i])
    {
        if (str[i] == '"')
        {
            ret++;
            i++;
            trig = 1;
            while (str[i])
            {
                if (str[i] == '"' && trig == 0)
                    trig = 1;
                else if (str[i] == '"')
                    trig = 0;
                if (str[i] == ' ' && trig == 0)
                    break;
                i++;
            }
        }
        else if (str[i] != ' ' || str[i] == '\'')
            sizelen_norm(&i, &ret, str);
        if (str[i] == '"' || str[i] == '\'' || str[i] == ' ')
            i++;
    }
    return (ret);
}

char     *singlequote(char    *str, int   *s, int i)
{
    char    *ret;
    int     trig;

    trig = 1;
    while (str[*s + i])
    {
        if (str[*s + i] == '\'' && trig == 0)
            trig = 1;
        else if (str[*s + i] == '\'')
            trig = 0;
        if (str[*s + i] == ' ' && trig == 0)
            break;
        *s = *s + 1;
    }
    ret = ft_substr(str + i, 0, *s);
    return (ret);
}

char     *doublequote(char    *str, int   *s, int i)
{
    char    *ret;
    int     trig;

    trig = 1;
    while (str[*s + i])
    {
        if (str[*s + i] == '"' && trig == 0)
            trig = 1;
        else if (str[*s + i] == '"')
            trig = 0;
        if (str[*s + i] == ' ' && trig == 0)
            break;
        *s = *s + 1;
    }
    ret = ft_substr(str + i, 0, *s);
    return (ret);
}

char    *get_arg(char   *str, int   *r)
{
    int     i;
    char    *ret;
    int     s;

    i = *r;
    s = 1;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\'')
        ret = singlequote(str, &s, i);
    else if (str[i] == '"')
        ret = doublequote(str, &s, i);
    else
    {
        while (str[s + i] && str[s + i] != ' ')
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

    size = sizelen(str, 0, 0);
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