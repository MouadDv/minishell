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
        fprintf(stderr, "[cmd] == > %s\n", tmp->cmd);
        while (tmp->args[i])
        {
            printf ("Arg[%d]. ========> %s\n",i, tmp->args[i]);
            i++;
        }
        
        i = 0;
        tmp2 = tmp->redirections;
        while (tmp2)
        {
            fprintf (stderr, " {%d}     [type] ====== > [%c]\n",h, tmp2->type);
            fprintf (stderr, " {%d}     [argument] == > %s\n",h, tmp2->arg);
            h++;
            tmp2 = tmp2->next;
        }
        i = 0;
        h = 0;
        tmp = tmp->next;
    }
    
}

void    get_redir(char  *str, t_red *red, int *r)
{
    if (str[0] == '<' && str[1] == '<')
    {
        red->type = 'h';
        subarg(r, 2, str, red);
    }
    else if (str[0] == '>' && str[1] == '>')
    {
        red->type = 'a';
        subarg(r, 2, str, red);
    }
    else if (str[0] == '>')
    {
        red->type = 'o';
        subarg(r, 2, str, red);
    }
    else if (str[0] == '<')
    {
        red->type = 'i';
        subarg(r, 2, str, red);
    }
}

void    get_cmd(char   *str, t_cmd   *strct, int    *r)
{
    int i;

    i = 0;
    if (str[i] != '<' && str[i] != '>' && str[i] != '|')
    {
        while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
            i++;
        strct->cmd = ft_substr(str, 0, i);
        *r = *r + i - 1;
    }
}

int    parce_syntax(char   *str, t_cmd   *strct)
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
        else if (str[i] == '|')
        {
            strct->next = alloc_cmd_s();
            strct = strct->next;
        }
        else if (str[i] != ' ')
        {
            get_cmd(str + i, strct, &i);
            strct->args = splitargs(strct->cmd);
        }
        i++;
    }
    return (1);
}

int    parse_and_exec(char *buf, t_node	*node)
{
    char    *str;
    t_cmd   *strct;

    strct = alloc_cmd_s();
    if (!strct)
        return (0);
    str = ft_strtrim(buf, " ");
    if (parce_syntax(str, strct) == 0)
        return (0);
    if (data_proc(strct, node) == 0)
        return (0);
    print_strct(strct);
    free_strct(strct, NULL, NULL, NULL);
    free_null(str);
    return (1);
}