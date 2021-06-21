#include "minishell.h"

int	add_agn(char *str, t_env *result, t_vars *vars)
{
	char	*value;
	t_env	*block;

	value = get_env_value(str, vars->agn);
	if (value)
		value = ft_strdup(value);
	else
		return (0);
	result->value = value;
	result->key = ft_strdup(str);
	block = blockcpy(result);
	if (add_to_exp(vars->env, block) < 0 ||
			add_to_exp(vars->exp, block) < 0)
		return (-1);
	return (1);
}

int	export_only(char *str, t_env *result, t_vars * vars)
{
	t_env	*tmp;
	t_env	*cpy;

	tmp = vars->exp;
	if (add_agn(str, result, vars))
		return (1);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
		{
			cpy = blockcpy(tmp);
			if (!cpy)
				return (-1);
			if (add_to_exp(vars->env, cpy) < 0
				|| add_to_exp(vars->exp, cpy) < 0)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	if (new_expblock(str, "\0", result) == 0)
		return (-1);
	if (add_to_exp(vars->exp, result) < 0)
		return (-1);
	return (1);
}
