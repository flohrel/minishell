/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/01 15:33:42 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_str(char *str, t_env *env, t_vars *vars)
{
	t_env	*result;
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	result = lst_alloc(1, sizeof(t_env), vars);
	if (!result)
		return (0);
	result = new_envblock(str, result, vars);
	if (!result)
		return (0);
	result->next = NULL;
	tmp->next = result;
	return (1);
}

int	export(char **args, t_vars *vars)
{
	export_str(args[0], vars->env, vars);
	return (1);
}
