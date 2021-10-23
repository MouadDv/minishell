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
    int end;
    while (str[i] == ' ' && str[i])
            i++;
    end = end_of_delimiter(str + i);
    red->arg = ft_substr(str, i, end);
    *r = *r + i + end - 1;
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	int		sum;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = strlen((char *)s1);
	lens2 = strlen((char *)s2);
	sum = lens1 + lens2;
	newstr = (char *)malloc(sum + 1);
	if (newstr == NULL)
		return (NULL);
	ft_memcpy1(newstr, s1, lens1);
	ft_memcpy1(newstr + lens1, s2, lens2 + 1);
	return (newstr);
}

void	*ft_memcpy1(void *dest, const void *src, size_t n)
{
	char	*psrc;
	char	*pdest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	psrc = (char*)src;
	pdest = (char*)dest;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}