#include "minishell.h"


void print_strct(t_cmd *strct)
{
    t_cmd *tmp;
    t_red *tmp2;
    int i;

    tmp = strct;
    i = 0;
    while (tmp)
    {
        fprintf(stderr, "[cmd] == > %s\n", tmp->cmd);
        while (tmp->args[i])
        {
            fprintf(stderr, "[arg][%d] ============ > %s\n", i, tmp->args[i]);
            i++;
        }
        i = 0;
        tmp2 = tmp->redirections;
        while (tmp2)
        {
            fprintf (stderr, "      [type] ====== > %c\n", tmp2->type);
            fprintf (stderr, "      [filename] == > %s\n", tmp2->filename);
            fprintf (stderr, "      [delimiter] = > %s\n", tmp2->delimiter);
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

int     next_char(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != ' ')
        i++;
    return (i);
}

int     end_of_command(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '|')
        i++;
    return (i);
}

int    parce_syntax_one(char   *str, t_cmd   *strct)
{
    strct->redirections = alloc_red_s();
    if (!strct->redirections)
        return (0);
    if (str[0] == '>' && str[1] == '>')
    {
        strct->redirections->type = 'a';
        strct->redirections->filename = ft_substr(str, 3, next_char(str + 3));
        strct->cmd = ft_substr(str, 3 + next_char(str + 3), end_of_command(str));
        strct->args = ft_split(strct->cmd, ' ');
    }
    // else if (str[0] == '>' && str[1] != '>')
    // else if (str[0] == '<' && str[1] == '<')
    // else if (str[0] == '<' && str[1] != '<')
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