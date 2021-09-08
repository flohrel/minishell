/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/08 17:20:57 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;

	if (node == NULL)
		return ;
	param = node->data;
	args = list_to_tab(param->arg, vars);
	if (param && (!(param->path) || ft_strcmp(param->path, "export") == 0))
		if (handle_assign(vars, param->assign) < 0)
			clean_exit(vars, NULL, NULL, errno);
	find_cmd(param, args, env_to_tab(vars->env, vars), vars);
}

void	exec_pipeline(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	int	fdes[2];

	cmd->std_out = dup(FD_OUT);
	cmd->std_in = dup(FD_IN);
	pipe(fdes);
	cmd->pipe[FD_OUT] = fdes[FD_OUT];
	cmd->pipe[FD_IN] = fdes[FD_IN];
	set_flag(&cmd->io_bit, PIPE_IN);
	exec_command(vars, node->left);
	node = node->right;
	while (node && (node->type == NODE_PIPE))
	{
		set_flag(&cmd->io_bit, PIPE_OUT);
		pipe(fdes);
		cmd->pipe[FD_OUT] = fdes[FD_OUT];
		exec_command(vars, node->left);
		cmd->pipe[FD_IN] = fdes[FD_IN];
		node = node->right;
	}
	cmd->io_bit = -1;
	exec_command(vars, node);
}

void	exec_job(t_vars *vars, t_ast *node)
{
	parse_expansion(vars, node);
	if (check_flag(node->type, NODE_PIPE))
		exec_pipeline(vars, &vars->cmd, node);
	else
		exec_command(vars, node);
}

void	exec_sub(t_vars *vars, t_ast *node)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		clean_exit(vars, NULL, NULL, errno);
	else if (pid == 0)
	{
		clear_flag(&node->type, NODE_SUB);
		exec_list(vars, node, true);
		exit(exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
}

void	exec_list(t_vars *vars, t_ast *node, bool is_exec)
{
	vars->cmd.io_bit = 0;
	vars->cmd.std_out = -1;
	vars->cmd.std_in = -1;
	if (!node)
		return ;
	if (node && check_flag(node->type, NODE_SUB))
		exec_sub(vars, node);
	else if (is_exec == true)
	{
		if (!check_flag(node->type, NODE_LIST) && (is_exec == true))
			exec_job(vars, node);
		else
			exec_job(vars, node->left);
	}
	if ((node->type == NODE_AND) && (exit_status == 0))
		exec_list(vars, node->right, true);
	else if ((node->type == NODE_OR) && (exit_status))
		exec_list(vars, node->right, true);
	else
		exec_list(vars, node->right, false);
}

void	exec_ast(t_vars *vars, t_ast *node)
{
	if (!node)
		return ;
	exec_list(vars, node, true);
	close(3);
	close(4);
}
