#include "minishell.h"

char	*env_val(char	*name, t_node	*node)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (node != NULL)
	{
		if (!ft_strncmp(name, node->name, ft_strlen(name) + 1))
		{
			ret = ft_strdup(node->val);
			break ;
		}
		node = node->next;
	}
	if (ret == NULL)
		ret = ft_strdup("");
	return (ret);
}
