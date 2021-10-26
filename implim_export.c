/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implim_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:38:33 by sbensarg          #+#    #+#             */
/*   Updated: 2021/10/26 15:30:00 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_global_export(char **ptr, t_node	*node)
{
    int i;
    int j;
    char *value;
    int flag;
    char    *s;

    i = 1;
    j = 0;
    flag = 0;
    while (ptr[i])
    {
        if ((ft_strncmp(ptr[i], "=",1)) != 0)
        {
        
            if((s = ft_strchr(ptr[i], '=')))
            {
                *s = '\0';
                value = ft_strjoin("=\"", (s+1));
                value = ft_strjoin(value, "\"");
                ft_check(&node, ptr[i], value, &flag);
                if (flag != 2)
                {
                    int ret;
                    ret= ft_check_valid_identifier(ptr[i]);
                    if (ret != 1)
                        test_add(&node, ptr[i], value);
                    else 
                        printf ("bash: export: « %s%s» : identifiant non valable\n", ptr[i], value);
                }
            }
            else
            {
                value = ft_strdup("");
                ft_check(&node, ptr[i], value, &flag);
                if (flag != 2)
                {
                    int ret;
                    ret= ft_check_valid_identifier(ptr[i]);
                    if (ret != 1)
                        test_add(&node, ptr[i], value);
                    else 
                        printf ("bash: export: « %s » : identifiant non valable\n", ptr[i]);
                }
            }
        }
        else
            printf ("bash: export: « %s » : identifiant non valable\n", ptr[i]);
        i++;
    }
}

int ft_check_valid_identifier(char *name)
{
    if (!((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z')))
        return (1);
    return (0);
}

int ft_check(t_node **head,char *name, char *val, int *flag)
{
   t_node *cur;
   cur = *head;
   
    while (cur != NULL)
    {

        if (ft_strncmp(cur->name, name, strlen(name)) == 0)
        {
            
            *flag = 2;
            if (cur->val != NULL && *val != '\0')
            {
                free(cur->val);
                cur->val = ft_strdup(val);
            }
            return (0);
        }
             
        cur = cur->next;
    }
   return (1);
}

void test_add(t_node **head, char *name, char *val)
{
    t_node  *newnode;
    t_node  *lastnode;

    newnode = malloc(sizeof(t_node));
    newnode->name = ft_strdup(name);
    newnode->val = ft_strdup(val);
    newnode->next = NULL;
    if(*head == NULL)
         *head = newnode;
    else
    {
        lastnode = *head;
        while(lastnode->next != NULL)
            lastnode = lastnode->next;
        lastnode->next = newnode;
    }

}
void	init_struct(char **envp, t_node **head)
{
    int     i;
    char    *s;
    char    *key;

    i = 0;
  
    while (envp[i])
    {
        if((s = ft_strchr(envp[i], '=')))
        {
            *s = '\0';
            key = ft_strjoin("=\"", (s+1));
            key = ft_strjoin(key, "\"");
            test_add(head, envp[i], key);
        }
        i++;
    }
}

int len_list(t_node *head)
{
    t_node *cur;
    int i;
    
    cur = head;
    i = 0;
    while (cur != NULL)
    {
        i++;
       cur = cur->next;
    }
    return (i);
}

t_node	*copy_list(t_node *node)
{
	t_node	*cur;
	t_node	*newlist;
	t_node	*tail;

	cur = node;
	newlist = NULL;
	tail = NULL;
	
	while (cur != NULL)
	{
		if (newlist == NULL)
		{
			newlist = (t_node *)malloc(sizeof(t_node));
			newlist->name = cur->name;
			newlist->val = cur->val;
			newlist->next = NULL;
			tail = newlist;
		}
		else
		{
			tail->next = (t_node *)malloc(sizeof(t_node));
			tail = tail->next;
			tail->name = cur->name;
			tail->val = cur->val;
			tail->next = NULL;
		}
		cur = cur->next;
	}
	return (newlist);
}

void ft_sort_list(t_node *head)
{
    int len;
    int i;
	
   	len = len_list(head);
    for(i=0; i<len; i++)
    {
        t_node *tmp1 = head;
        t_node *tmp2 = (tmp1 != NULL) ? tmp1->next : NULL;
        while((tmp1 != NULL) && (tmp2 != NULL))
        {
            if(ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name)) > 0)
            {
                char *wrd;
                char *val;
                
                wrd = tmp1->name;
                tmp1->name = tmp2->name;
                tmp2->name = wrd;
                
                val = tmp1->val;
                tmp1->val = tmp2->val;
                tmp2->val = val;
            }
            tmp1=tmp1->next;
            tmp2 = tmp2->next;
        }
        tmp1 = head;
    }
}

void  ft_export(t_node *head)
{
    t_node   *temp;

    temp = head;
    while (temp != NULL)
    {
        write(1, "declare -x ", 11);
        write(1, temp->name, ft_strlen(temp->name));
        write(1, temp->val, ft_strlen(temp->val));
        write(1, "\n",1);
        temp = temp->next;
    }
   
}