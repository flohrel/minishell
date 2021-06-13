/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/11 19:23:07 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			new_expblock(char *key, char *value, t_env *block)
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
		free_block(block);
		return (1);
	}
	return (0);
}

static void	add_to_exp(t_env *exp, t_env *block)
{
	t_env	*tmp;
	t_env	*stack;

	tmp = exp;
	stack = blockcpy(block);
	if (!tmp)
	{
		tmp = stack;
		return ;
	}
	while (tmp && tmp->next)
	{
		if (replace_value(tmp, stack))
			return ;
		tmp = tmp->next;
	}
	if (replace_value(tmp, stack))
		return ;
	tmp->next = stack;
}
//SEGFAULT JE SAIS PAS OU
static int	export_str(char *str, t_vars *vars)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	result->next = NULL;
	if (new_envblock(str, result) == -1)
	{
		if (new_expblock(str, "\0", result) < 0)
			return (0);
	}
	else
		add_to_exp(vars->env, result);
	add_to_exp(vars->exp, result);
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
			return (-1);
		i++;
	}
	if (ft_tablen(args) == 0)
	{
		print_sorted_env(vars->exp);
	}
	return (1);
}
