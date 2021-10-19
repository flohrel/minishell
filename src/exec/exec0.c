/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:39 by mtogbe            #+#    #+#             */
/*   Updated: 2021/10/19 19:09:25 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_list2(t_vars *vars, t_ast *node, bool is_exec)
{
	int	ret;

	ret = 0;
	if (is_exec == true)
	{
		if (!check_flag(node->type, NODE_LIST) && (is_exec == true))
			ret = exec_job(vars, node);
		else if (node->left && check_flag(node->left->type, NODE_LIST))
			ret = exec_list(vars, node->left, is_exec);
		else
			ret = exec_job(vars, node->left);
	}
	if (ret == -1)
		return (ret);
	if (check_flag(node->type, NODE_AND) && (g_sig.exit_status == 0))
		ret = exec_list(vars, node->right, true);
	else if (check_flag(node->type, NODE_OR) && (g_sig.exit_status))
		ret = exec_list(vars, node->right, true);
	else
		ret = exec_list(vars, node->right, false);
	return (ret);
}

int	exec_list(t_vars *vars, t_ast *node, bool is_exec)
{
	int	ret;

	ret = 0;
	vars->io.flag = 0;
	if (!node)
		return (0);;
	if (node && check_flag(node->type, NODE_SUB))
	{
		if (is_exec == false)
			return (0);
		exec_sub(vars, node);
	}
	else
		ret = exec_list2(vars, node, is_exec);
	return (ret);
}

void	exec_ast(t_vars *vars, t_ast *node)
{
	vars->io.std_out = dup(FD_OUT);
	vars->io.std_in = dup(FD_IN);
	if (!node)
		return ;
	exec_list(vars, node, true);
	close(vars->io.std_in);
	close(vars->io.std_out);
}
