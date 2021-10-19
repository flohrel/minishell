/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:28:13 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/24 20:19:20 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exp_print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

void	env_print(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key)
			ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		if (tmp->value)
			ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

int	print_env(char **args, t_vars *vars)
{
	if (ft_tablen(args) > 0)
		return (errormsg("env :", " too many arguments"));
	env_print(vars->env);
	return (0);
}
