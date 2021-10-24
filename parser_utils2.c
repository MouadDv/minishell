#include "minishell.h"

int     sizelen(char    *str)
{
    int     ret;
    int     i;
    int     trig;

    ret = 0;
    i = 0;
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
        else if (str[i] == '\'')
        {
            ret++;
            i++;
            trig = 1;
            while (str[i])
            {
                if (str[i] == '\'' && trig == 0)
                    trig = 1;
                else if (str[i] == '\'')
                    trig = 0;
                if (str[i] == ' ' && trig == 0)
                    break;
                i++;
            }
        }
        else if (str[i] != ' ')
        {
            ret++;
            while (str[i] && str[i] != ' ')
                i++;
        }
        if (str[i] == '"' || str[i] == '\'' || str[i] == ' ')
            i++;
    }
    return (ret);
}

char    *get_arg(char   *str, int   *r)
{
    int     i;
    char    *ret;
    int     s;
    int     trig;

    i = *r;
    s = 1;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\'')
    {
        trig = 1;
        while (str[s + i])
        {
            if (str[s + i] == '\'' && trig == 0)
                trig = 1;
            else if (str[s + i] == '\'')
                trig = 0;
            if (str[s + i] == ' ' && trig == 0)
                break;
            s++;
        }
        ret = ft_substr(str + i, 0, s);
    }
    else if (str[i] == '"')
    {
        trig = 1;
        while (str[s + i])
        {
            if (str[s + i] == '"' && trig == 0)
                trig = 1;
            else if (str[s + i] == '"')
                trig = 0;
            if (str[s + i] == ' ' && trig == 0)
                break;
            s++;
        }
        ret = ft_substr(str + i, 0, s);
    }
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