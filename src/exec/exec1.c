/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/20 19:44:31 by flohrel          ###   ########.fr       */
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
	if (param && !(param->path))
	{
		if (handle_assign(vars, param->assign) < 0)
			clean_exit(vars, NULL, NULL, errno);
	}
	else
		find_cmd(param, args, env_to_tab(vars->env, vars), vars);
}

void	pipe_init(int fdes, t_cmd *cmd)
{
	pipe(fdes);
	set_flag(&cmd->io_bit, PIPE_IN);
	cmd->pipe[FD_IN] = fdes[FD_IN];
}

void	set_pipe(int fdes, t_cmd *cmd)
{
	pipe(fdes);
	set_flag(&cmd->io_bit, PIPE_OUT);
}

void	exec_pipeline(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	int		pid;
	int		fdes[2];
	t_param	*param;

	pipe_init(fdes, cmd);
	while (node && (node->type == NODE_PIPE))
	{
		cmd->pipe[FD_OUT] = fdes[FD_OUT];
		param = node->data;
		if (handle_builtin(param->path, argv, env_to_tab(vars->env, vars) param))
			continue ;
		pid = fork();
		if (pid < 0)
			clean_exit(vars, NULL, NULL, errno);
		if (pid == 0)
			exec_cmd(vars, node->left);
		else
		{
			cmd->pipe[FD_IN] = fdes[FD_IN];
			node = node->right;
			set_pipe(fdes, cmd);
		}
	}

/*	exec_command(vars, node->left);
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
	cmd->io_bit = -256;
	exec_command(vars, node);*/
}

void	exec_job(t_vars *vars, t_ast *node)
{
	parse_expansion(vars, node);
	display_tree(vars->exec_tree, 0, 0);
	vars->cmd.std_in = dup(FD_IN);
	vars->cmd.std_out = dup(FD_OUT);
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
		exit(g_sig.exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
}
