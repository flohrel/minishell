/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:39 by mtogbe            #+#    #+#             */
/*   Updated: 2021/10/08 20:10:40 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_list2(t_vars *vars, t_ast *node, bool is_exec)
{
	if (is_exec == true)
	{
		if (!check_flag(node->type, NODE_LIST) && (is_exec == true))
			exec_job(vars, node);
		else if (node->left && check_flag(node->left->type, NODE_LIST))
			exec_list(vars, node->left, is_exec);
		else
			exec_job(vars, node->left);
	}
	if (check_flag(node->type, NODE_AND) && (g_sig.exit_status == 0))
		exec_list(vars, node->right, true);
	else if (check_flag(node->type, NODE_OR) && (g_sig.exit_status))
		exec_list(vars, node->right, true);
	else
		exec_list(vars, node->right, false);
}

void	exec_list(t_vars *vars, t_ast *node, bool is_exec)
{
	vars->io.flag = 0;
	if (!node)
		return ;
	if (node && check_flag(node->type, NODE_SUB))
	{
		if (is_exec == false)
			return ;
		exec_sub(vars, node);
	}
	else
		exec_list2(vars, node, is_exec);
}

void	exec_ast(t_vars *vars, t_ast *node)
{
	vars->io.std_out = dup(FD_OUT);
	vars->io.std_in = dup(FD_IN);
	display_tree(vars->exec_tree, 0, 0);
	if (!node)
		return ;
	exec_list(vars, node, true);
	close(vars->io.std_in);
	close(vars->io.std_out);
}
