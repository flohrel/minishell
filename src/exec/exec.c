/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/30 03:40:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_command(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	t_param	*param;
	char	**args;

	(void)cmd;
	vars->last_status = 0;	
	if (node == NULL)
		return (-1);
	param = node->data;
	args = list_to_tab(param->arg, vars);
	if (param && !(param->path))
		handle_assign(vars, param->assign);
	if (find_cmd(param, args,
		env_to_tab(vars->env, vars), vars))
		return (3);
	return (-1);
}

void	exec_pipeline(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	int	fdes[2];

	cmd->std_out = dup(FD_OUT);
	cmd->std_in = dup(FD_IN);
	pipe(fdes);
	cmd->pipe[FD_OUT] = fdes[1];
	cmd->pipe[FD_IN] = fdes[0];
	set_flag(&cmd->io_bit, PIPE_IN);
	exec_command(vars, cmd, node->left);
	node = node->right;
	while (node && (node->type == NODE_PIPE))
	{
		set_flag(&cmd->io_bit, PIPE_OUT);
		pipe(fdes);
		cmd->pipe[FD_OUT] = fdes[1];
		exec_command(vars, cmd, node->left);
		cmd->pipe[FD_IN] = fdes[0];
		node = node->right;
	}
	cmd->io_bit = -1;
	exec_command(vars, cmd, node);
	//close_handle(vars);
}

void	exec_job(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_PIPE)
		exec_pipeline(vars, &vars->cmd, node);
	else
		exec_command(vars, &vars->cmd, node);
}

void	exec_cmdline(t_vars *vars, t_ast *node)
{
	vars->cmd.io_bit = 0;
	vars->cmd.std_out = -1;
	vars->cmd.std_in = -1;
	if (node && node->type != NODE_SEQ)
		exec_job(vars, node);
	else if (node->left)
		exec_job(vars, node->left);
	if (node->type == NODE_SEQ && node->right)
	{
		exec_cmdline(vars, node->right);
	}
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	(void)vars;
	(void)root;
	exec_cmdline(vars, root);
	close(3);
	close(4);
}
