/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/03 18:46:43 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_str(char *str, t_vars *vars)
{
	t_env	*result;
	t_env	*tmp;

	write(1,"o",1);
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
	write(1,"o",1);
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
