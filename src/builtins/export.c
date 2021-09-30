/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/30 19:10:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	new_expblock(char *key, char *value, t_env *block)
{
	block->key = ft_strdup(key);
	if (!(block->key))
		return (-1);
	block->value = ft_strdup(value);
	if (!(block->value))
		return (-1);
	block->next = NULL;
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

int	add_to_exp(t_env **exp, t_env *block)
{
	t_env	*tmp;
	t_env	*stack;
	int		ret;

	tmp = *exp;
	stack = blockcpy(block);
	if (!stack)
		return (-1);
	if (!tmp && init_exp(exp, stack))
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
	int		ret;

	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	if (new_envblock(str, result) == -1)
	{
		if (export_only(str, result, vars, &ret) < 0)
			return (ret);
	}
	else if (!result->key || !result->value)
		return (0);
	else if (!(ft_strischarset(result->key, "+-/*.= $")))
	{
		if (add_to_exp(&vars->env, result) < 0
			|| add_to_exp(&vars->exp, result) < 0)
			return (0);
	}
	else
		return (ret_context(result));
	free_block(result);
	return (1);
}

int	export(char **args, t_vars *vars)
{
	int	i;
	int	ret;
	int	exit_st;

	exit_st = 0;
	i = 0;
	while (args && args[i])
	{
		if (ft_strcmp("", args[i]) == 0)
			exit_st = errormsg("minishell: export: << >> ",
					"invalid identifier.");
		else
		{
			ret = export_str(args[i], vars);
			if (!ret)
				clean_exit(vars, NULL, NULL, errno);
			else if (ret == -1)
				exit_st = exp_error(args[i]);
		}
		i++;
	}
	if (ft_tablen(args) == 0)
		print_sorted_env(vars->exp);
	return (exit_st);
}
