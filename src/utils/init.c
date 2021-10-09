/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:48:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/30 17:24:28 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_vars(t_vars *vars)
{
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
	vars->ptr_list = NULL;
	vars->nb_pipes = 0;
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
	g_sig.exit_status = 0;
}
