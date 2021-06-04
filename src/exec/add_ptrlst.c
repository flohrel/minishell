#include "minishell.h"

void	*add_to_ptrlst(void *content, t_vars *vars)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (NULL);
	ft_lstadd_front(&(vars->ptr_list), new);
	return (new);
}

