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

static int	export_str(char *str, t_vars *vars)
{
	t_env	*result;
	t_env	*tmp;

	tmp = vars->env;
	while (tmp->next)
		tmp = tmp->next;
	result = malloc(sizeof(t_env));
	if (!result)
		return (0);
	result->next = NULL;
	if (new_envblock(str, result) == -1)
	{
		if (new_expblock(str, "''", result) < 0)
			return (0);
	}
	else
		tmp->next = result;
	if (!(vars->exp))
		vars->exp = result;
	else
		vars->exp->next = result;
//check si la key existe deja, et si c'est le casm changer uniquement la value
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
		print_sorted_env(vars->env);
		print_sorted_env(vars->exp);
	}
	return (1);
}
