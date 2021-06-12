/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:48:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/12 16:45:07 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_vars(t_vars *vars)
{
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
	vars->ptr_list = NULL;
}

void	init(t_vars *vars, char **envp)
{
	errno = 0;
	vars->env = parse_env(envp, vars);
	vars->exit_status = 0;
}
