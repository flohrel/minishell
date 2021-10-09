/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:22:15 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/22 14:32:34 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ret_context(t_env *result)
{
	free_block(result);
	return (-1);
}

int	exp_error(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd("<< ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(" >> ", STDERR_FILENO);
	ft_putstr_fd(": Not valid in this context\n", STDERR_FILENO);
	return (1);
}

int	add_agn(char *str, t_env *result, t_vars *vars)
{
	char	*value;
	t_env	*block;

	value = get_env_value(str, vars->agn);
	if (!value)
		return (0);
	result->value = ft_strdup(value);
	result->key = ft_strdup(str);
	result->next = NULL;
	if (!result->key || !result->value)
		return (-1);
	block = blockcpy(result);
	if (!block)
		return (-1);
	if (add_to_exp(&vars->env, block) < 0
		|| add_to_exp(&vars->exp, block) < 0)
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
	if (add_to_exp(&vars->env, cpy) < 0
		|| add_to_exp(&vars->exp, cpy) < 0)
		return (-1);
	free_block(cpy);
	return (1);
}

int	export_only(char *str, t_env *result, t_vars *vars, int *ret)
{
	if (ft_strischarset(str, "+/-*.="))
	{
		*ret = -1;
		return (-1);
	}
	if (add_agn(str, result, vars))
		return (1);
	if (new_expblock(str, "\0", result) == 0)
	{
		*ret = 0;
		return (-1);
	}
	if (add_to_exp(&vars->exp, result) < 0)
	{
		*ret = 0;
		return (-1);
	}
	return (1);
}
