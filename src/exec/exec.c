/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/04 18:50:35 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;

	param = node->data;
	args = list_to_tab(param->arg, vars);
	if (find_builtin(param->path, args, vars))
		return ;
	else if (find_cmd(param->path, args,
				env_to_tab(vars->env, vars), vars))
		return ;
}

void	exec_pipeline(t_vars *vars, t_ast *node)
{
	(void)vars;
	(void)node;
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
	if (node->type == NODE_SEQ && node->right)
	{
		exec_cmdline(vars, node->right);
	}
	if (node->left)
		exec_job(vars, node->left);
	else if (node)
		exec_job(vars, node);
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	exec_cmdline(vars, root);
}
