/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/20 03:48:22 by flohrel          ###   ########.fr       */
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
	args = wildcard_convert(args, vars);
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
}

void	exec_job(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_PIPE)
		exec_pipeline(vars, &vars->cmd, node);
	else
		exec_command(vars, &vars->cmd, node);
}

void	exec_list(t_vars *vars, t_ast *node, bool is_exec)
{
	vars->cmd.io_bit = 0;
	vars->cmd.std_out = -1;
	vars->cmd.std_in = -1;
	if (!check_flag(node->type, NODE_LIST))
		exec_job(vars, node);
	else
	{
		if (is_exec == true)
			exec_job(vars, node->left);
		if ((node->type == NODE_AND) && (vars->exit_status == 0))
			exec_list(vars, node->right, true);
		else if ((node->type == NODE_OR) && (vars->exit_status))
			exec_list(vars, node->right, true);
		else
			exec_list(vars, node->right, false);
	}
}

void	exec_ast(t_vars *vars, t_ast *node)
{
	if (!node)
		return ;
	exec_list(vars, node, true);
	close(3);
	close(4);
}
