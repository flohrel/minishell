/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/20 00:23:10 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	t_param	*param;
	char	**args;

	(void)cmd;
	if (node == NULL)
		return (-1);
	param = node->data;
	args = list_to_tab(param->arg, vars);
	if (param && !(param->path))
		handle_assign(vars, param->assign);
	if (find_builtin(param->path, args, vars))
		return (1);
	if (find_cmd(param, args,
		env_to_tab(vars->env, vars), vars))
		return (3);
	return (-1);
}

void	exec_pipeline(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	int	fdes[2];

	pipe(fdes);
	cmd->pipe[FD_OUT] = fdes[1];
	cmd->pipe[FD_IN] = fdes[0];
	set_flag(&cmd->io_bit, PIPE_IN);
	exec_command(vars, cmd, node->left);
	node = node->right;
	while (node && (node->type == NODE_PIPE))
	{
		set_flag(&cmd->io_bit, PIPE_OUT);
		close(cmd->pipe[FD_OUT]);
		pipe(fdes);
		cmd->pipe[FD_OUT] = fdes[1];
		exec_command(vars, cmd, node->left);
		close(cmd->pipe[FD_IN]);
		cmd->pipe[FD_IN] = fdes[0];
		node = node->right;
	}
	//set_flag(&cmd->io_bit, PIPE_OUT);
	cmd->io_bit = -1;
	cmd->pipe[FD_IN] = fdes[0];
	close(cmd->pipe[FD_OUT]);
	exec_command(vars, cmd, node);
	close(cmd->pipe[FD_IN]);
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

void	exec_cmdline(t_vars *vars, t_ast *node)
{
	vars->cmd.io_bit = 0;
	if (!node)
		return ;
	if (node->type != NODE_SEQ)
		exec_list(vars, node, true);
	else
	{
		if (node->left)
			exec_list(vars, node->left, true);
		if (node->right)
			exec_cmdline(vars, node->right);
	}
}
