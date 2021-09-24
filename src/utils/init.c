/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:48:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/24 17:56:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_vars(t_vars *vars)
{
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
	vars->ptr_list = NULL;
	vars->nb_pipes = 0;
	vars->pipes = NULL;
}

void	check_lvl(t_vars *vars)
{
	t_env	*tmp;
	char	*minishlvl;
	char	*new_value;
	int		value;

	value = 0;
	minishlvl = get_env_value("MINISHLVL", vars->env);
	if (minishlvl != NULL)
	{
		value = ft_atoi(minishlvl);
		value++;
		new_value = ft_itoa(value);
		set_env_value(vars->env, "MINISHLVL", new_value);
		free(new_value);
	}
	else
	{
		tmp = ft_calloc(1, sizeof(*tmp));
		new_expblock("MINISHLVL", "0", tmp);
		if ((add_to_exp(&vars->env, tmp) < 0)
			|| (add_to_exp(&vars->exp, tmp) < 0))
			clean_exit(vars, NULL, NULL, errno);
		free_block(tmp);
	}
	g_sig.minishlvl = value;
}

void	init(t_vars *vars, char **envp)
{
	errno = 0;
	if (envp[0])
	{
		vars->env = parse_env(envp);
		vars->exp = parse_env(envp);
	}
	else
	{
		vars->env = NULL;
		vars->exp = NULL;
	}
	vars->agn = NULL;
	up_shell_lvl(vars);
	check_lvl(vars);
	g_sig.exit_status = 0;
	g_sig.is_child = 0;
	g_sig.is_displayed = 1;
}
