#include "minishell.h"

void	print_strct(t_cmd	*strct)
{
	t_cmd	*tmp;
	t_red	*tmp2;
	int		i;
	int		h;

	tmp = strct;
	i = 0;
	h = 1;
	while (tmp)
	{
		fprintf(stderr, "[cmd] == > %s\n", tmp->cmd);
		while (tmp->args[i])
		{
			printf("Arg[%d]. ========> %s\n", i, tmp->args[i]);
			i++;
		}
		i = 0;
		tmp2 = tmp->redirections;
		while (tmp2)
		{
			fprintf(stderr, " {%d}     [type] ====== > [%c]\n", h, tmp2->type);
			fprintf(stderr, " {%d}     [argument] == > %s\n", h, tmp2->arg);
			h++;
			tmp2 = tmp2->next;
		}
		i = 0;
		h = 0;
		tmp = tmp->next;
	}
}
