#include "minishell.h"

int	export_only(char *str, t_env *result, t_env *exp, t_env *env)
{
	t_env	*tmp;
	t_env	*cpy;

	tmp = exp;
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
			cpy = blockcpy(tmp);
			if (!cpy)
				return (-1);
			if (add_to_exp(env, cpy) < 0
				|| add_to_exp(exp, cpy) < 0)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	if (new_expblock(str, "\0", result) == 0)
		return (-1);
	if (add_to_exp(exp, result) < 0)
		return (-1);
	return (1);
}
