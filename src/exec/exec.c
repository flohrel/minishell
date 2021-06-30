/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/28 21:57:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;

	param = node->data;
	args = list_to_tab(param->arg, vars);
/*	if (vars->pipes &&  vars->pipes->prev &&
			vars->pipes->prev->node->type == NODE_CMD)
	{
		close(vars->cmd.pipe[FD_OUT]);
		dup2(vars->cmd.pipe[FD_IN], FD_IN);
	}
	else
		add_pipe(vars);*/
	if (param && !(param->path))
		handle_assign(vars, param->assign);
	if (find_builtin(param->path, args, vars))
		return (1);
	if (find_cmd(param, args,
		env_to_tab(vars->env, vars), vars))
		return (3);
	return (-1);
}

void	exec_pipeline(t_vars *vars, t_ast *node)
{
//	add_pipe(vars, node);
	if (pipe(vars->cmd.pipe) < 0)
		return ;//exit ?
	dup2(vars->cmd.pipe[FD_OUT], FD_OUT);
	if (node->left)
		exec_command(vars, node->left);
	if (node->right && node->right->type == NODE_PIPE)
		exec_pipeline(vars, node->right);
	else if (node->right)
		exec_command(vars, node->right);
}

void	exec_job(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_PIPE)
		exec_pipeline(vars, node);
	else if (node->type == NODE_CMD) 
		exec_command(vars, node);
}

void	exec_cmdline(t_vars *vars, t_ast *node)
{
	init_cmd(&vars->cmd);
	if (node && node->type != NODE_SEQ)
		exec_job(vars, node);
	else if (node && node->left)
		exec_job(vars, node->left);
	if (node && node->type == NODE_SEQ && node->right)
	{
		exec_cmdline(vars, node->right);
	}
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	(void)vars;
	(void)root;
	exec_cmdline(vars, root);
}
