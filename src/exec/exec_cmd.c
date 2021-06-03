/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/03 15:57:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_command(t_vars *vars, t_ast *node)
{
}

void	exec_pipeline(t_vars *vars, t_ast *node)
{
}

void	exec_job(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_PIPE)
		exec_pipeline(vars, node);
	else
		exec_command(vars, node);
}

void	exec_cmdline(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_SEQ)
		exec_cmdline(vars, node->right);
	exec_job(vars, node->left);
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	exec_cmdline(vars, root);
}
