#include "builtins.h"

int	add_agn(char *str, t_env *result, t_vars *vars)
{
	char	*value;
	t_env	*block;

	value = get_env_value(str, vars->agn);
	if (value)
	{
		value = ft_strdup(value);
		if (!value)
			return (-1);
	}
	else
		return (0);
	result->value = value;
	result->key = ft_strdup(str);
	if (!result->key)
		return (-1);
	block = blockcpy(result);
	if (!block)
		return (-1);
	if (add_to_exp(vars->env, block) < 0
			|| add_to_exp(vars->exp, block) < 0)
		return (-1);
	free_block(block);
	return (1);
}

int	export_found(t_env *tmp, t_vars *vars)
{
	t_env	*cpy;
	
	cpy = blockcpy(tmp);
	if (!cpy)
		return (-1);
	if (add_to_exp(vars->env, cpy) < 0
			|| add_to_exp(vars->exp, cpy) < 0)
		return (-1);
	free_block(cpy);
	return (1);
}

int	export_only(char *str, t_env *result, t_vars *vars)
{
	t_env	*tmp;

	tmp = vars->exp;
	if (ft_strischarset(str, "+/-*.="))
		return (errormsg("export : Not valid in this context : ",
				str));
	if (add_agn(str, result, vars))
		return (1);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key) == 0)
			if (export_found(tmp, vars) < 0)
				return (-1);
		tmp = tmp->next;
	}
	if (new_expblock(str, "\0", result) == 0)
		return (-1);
	if (add_to_exp(vars->exp, result) < 0)
		return (-1);
	return (1);
}
