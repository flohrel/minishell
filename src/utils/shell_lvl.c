/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:25:55 by mtogbe            #+#    #+#             */
/*   Updated: 2021/08/06 16:15:02 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	up_shell_lvl(t_vars *vars)
{
	int		lvl;
	char	*lvlstr;
	int		shlvl;
	char	*nb;

	lvl = 0;
	shlvl = 0;
	if (vars->env)
		nb = (get_env_value("SHLVL", vars->env));
	if (nb)
		lvl = ft_atoi(nb);
	if (!lvl)
		lvl = ++shlvl;
	else
		shlvl = ++lvl;
	lvlstr = ft_itoa(lvl);
	vars->env = set_env_value(vars->env, "SHLVL", lvlstr);
	if (!vars->env)
		clean_exit(vars, NULL, NULL, errno);
	vars->exp = set_env_value(vars->exp, "SHLVL", lvlstr);
	if (!vars->exp)
		clean_exit(vars, NULL, NULL, errno);
	free(lvlstr);
	return (1);
}
