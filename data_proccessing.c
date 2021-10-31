#include "minishell.h"

char	*get_name(char	*str)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != ' ')
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

char	*replace_env(char	*locat, char	*tmp, t_node	*node, int	flag)
{
	char	*fre;
	int		i;
	char	*ret;
	char	*name;
	char	*val;

	i = 0;
	tmp = locat;
	ret = ft_strdup("");
	while (locat[i])
	{
		if (locat[i] == '\'' && flag == 0)
			flag = 1;
		else if (locat[i] == '\'' && flag == 1)
			flag = 0;
		if (flag == 0 && locat[i] == '$' && locat[i + 1] != '"'
			&& locat[i + 1] != '$' && locat[i + 1] != '\0' && locat[i + 1] != ' ')
		{
			locat[i] = '\0';
			fre = ret;
			ret = ft_strjoin(ret, tmp);
			free_null(fre);
			name = get_name(locat + i + 1);
			tmp = locat + i + 1 + ft_strlen(name);
			val = env_val(name, node);
			if (ft_strlen(val) > 0)
			{
				fre = ret;
				ret = ft_strjoin(ret, ft_substr(val, 2, ft_strlen(val) - 3));
				free_null(fre);
			}
			free_null(name);
			free_null(val);
		}
		i++;
	}
	fre = ret;
	ret = ft_strjoin(ret, tmp);
	free_null(fre);
	return (ret);
}

int	data_proc(t_cmd	*strct, t_node	*node)
{
	int		i;
	t_red	*tmp2;
	char	*str;

	while (strct)
	{
		tmp2 = strct->redirections;
		i = 0;
		while (strct->args[i])
		{
			str = strct->args[i];
			strct->args[i] = replace_env(str, str, node, 0);
			free_null(str);
			i++;
		}
		while (tmp2)
		{
			str = tmp2->arg;
			tmp2->arg = replace_env(str, str, node, 0);
			free_null(str);
			tmp2 = tmp2->next;
		}
		strct = strct->next;
	}
	return (1);
}
