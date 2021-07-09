/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/24 20:13:22 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_expblock(char *key, char *value, t_env *block)
{
	block->key = ft_strdup(key);
	if (!(block->key))
		return (-1);
	block->value = ft_strdup(value);
	if (!(block->value))
		return (-1);
	return (1);
}

int	replace_value(t_env *env, t_env *block)
{
	if (ft_strcmp(env->key, block->key) == 0)
	{
		free(env->value);
		env->value = ft_strdup(block->value);
		if (!(env->value))
			return (-1);
		free_block(block);
		return (1);
	}
	return (0);
}

int	add_to_exp(t_env *exp, t_env *block)
{
	t_env	*tmp;
	t_env	*stack;
	int		ret;

	tmp = exp;
	stack = blockcpy(block);
	if (!stack)
		return (-1);
	if (!tmp && init_exp(&exp, stack))
		return (1);
	while (tmp && tmp->next)
	{
		ret = replace_value(tmp, stack);
		if (ret)
			return (1);
		else if (ret < 0)
			return (-1);
		tmp = tmp->next;
	}
	if (replace_value(tmp, stack))
		return (1);
	tmp->next = stack;
	return (1);
}

static int	export_str(char *str, t_vars *vars)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	if (new_envblock(str, result) == -1)
	{
		if (export_only(str, result, vars) < 0)
			return (0);
	}
	else if (!result->key || !result->value)
		return (0);
	else if ((ft_strischarset(result->key, "+/-*")) == 0)
	{
		if (add_to_exp(vars->env, result) < 0
			|| add_to_exp(vars->exp, result) < 0)
			return (0);
	}
	else
		errormsg("export : Not valid in this context : ", result->key);
	free_block(result);
	return (1);
}

int	export(char **args, t_vars *vars)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (!(export_str(args[i], vars)))
			clean_exit(vars, errno);
		i++;
	}
	if (ft_tablen(args) == 0)
	{
		print_sorted_env(vars->exp);
	}
	return (0);
}
