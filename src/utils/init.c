/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:48:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/21 03:48:55 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->redir[FD_IN] = -1;
	cmd->redir[FD_OUT] = -1;
	cmd->pipe[FD_IN] = -1;
	cmd->pipe[FD_OUT] = -1;
}

void	init_vars(t_vars *vars)
{
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
	vars->ptr_list = NULL;
	vars->pipes = NULL;
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
	exit_status = 0;
}
