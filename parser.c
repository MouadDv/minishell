#include "minishell.h"


void print_strct(t_cmd *strct)
{
    t_cmd *tmp;
    t_red *tmp2;
    int i;
    int h;

    tmp = strct;
    i = 0;
    h = 1;
    while (tmp)
    {
        //fprintf(stderr, "[cmd] == > %s\n", tmp->cmd);
        // while (tmp->args[i])
        // {
        //     fprintf(stderr, "[arg][%d] ============ > %s\n", i, tmp->args[i]);
        //     i++;
        // }
        i = 0;
        tmp2 = tmp->redirections;
        while (tmp2)
        {
            fprintf (stderr, " {%d}     [type] ====== > [%c]\n",h, tmp2->type);
            fprintf (stderr, " {%d}     [filename] == > %s\n",h, tmp2->filename);
            fprintf (stderr, " {%d}     [delimiter] = > [%s]\n",h, tmp2->delimiter);
            h++;
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    
}

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
    ret->delimiter = NULL;
    ret->filename = NULL;
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

void    get_redir(char  *str, t_red *red, int *r)
{
    int i;

    i = 0;
    if (str[i] == '<' && str[i + 1] == '<')
    {
        i += 2;
        red->type = 'h';
        red->filename = NULL;
        while (str[i] == ' ' && str[i])
            i++;
        red->delimiter = ft_substr(str, i, end_of_delimiter(str + i));
        *r = *r + i - 1;
    }
    else if (str[i] == '>' && str[i + 1] == '>')
    {
        i += 2;
        red->type = 'a';
        red->delimiter = NULL;
        while (str[i] == ' ' && str[i])
            i++;
        red->filename = ft_substr(str, i, end_of_delimiter(str + i));
        *r = *r + i - 1;
    }
}

int    parce_syntax_one(char   *str, t_cmd   *strct)
{
    t_red   *tmp;
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<' || str[i] == '>')
        {
            if (strct->redirections == NULL)
            {
                strct->redirections = alloc_red_s();
                tmp = strct->redirections;
            }
            else
            {
                tmp->next = alloc_red_s();
                tmp = tmp->next;
            }
            if (!tmp)
                return (0);
            get_redir(str + i, tmp, &i);
        }
        i++;
    }
    return (1);
}

int    parce_syntax_two(char   *str, t_cmd   *strct)
{
    t_cmd   *tmp;

    strlen(str);
    tmp = strct;
    return (0);
}

int    parse_data(char *buf)
{
    char    *str;
    t_cmd   *strct;

    strct = alloc_cmd_s();
    if (!strct)
        return (0);
    str = ft_strtrim(buf, " ");
    if (str[0] == '<' || str[0] == '>')
    {
        if (parce_syntax_one(str, strct) == 0)
            return (0);
    }
    else
    {
        if (parce_syntax_two(str, strct) == 0)
            return (0);
    }
    print_strct(strct);
    return (1);
}