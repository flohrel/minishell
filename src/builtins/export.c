/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/03 18:33:49 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	result = new_envblock(str, result);
	if (!result)
		return (0);
	result->next = NULL;
	tmp->next = result;
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
	//afficher la liste d'export
	//if (!args)
	return (1);
}
