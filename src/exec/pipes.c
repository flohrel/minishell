#include "minishell.h"

int	add_pipe(t_vars *vars, t_ast *node)
{
	t_pipes	*tmp;

	tmp = vars->pipes;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_pipes));
		if (tmp->next)
			return (-1);
		tmp->next->p_open = 1;
		tmp->next->node = node;
		tmp->next->prev = tmp;
	}
	else
	{
		tmp->next = malloc(sizeof(t_pipes));
		if (tmp->next)
			return (-1);
	}
	return (1);
}
