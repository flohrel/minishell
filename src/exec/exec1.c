/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/10/01 17:56:20 by flohrel          ###   ########.fr       */
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
	if (param && !(param->path) && param->assign
		&& handle_assign(vars, param->assign) < 0)
		clean_exit(vars, NULL, NULL, errno);
	find_cmd(param, args, env_to_tab(vars->env, vars), vars);
}

void	fork_pipeline(t_vars *vars, t_ast *node)
{
	int		status;
	int		ct;
	pid_t	last;
	int		count;

	count = 0;
	ct = 0;
	vars->nb_pipes = 0;
	while (node && (node->type == NODE_PIPE))
	{
		exec_pipeline(vars, node->left, ct);
		ct++;
		node = node->right;
	}
	last = exec_last_pipe(vars, node);
	ct++;
	while (count < ct)
	{
		if ((waitpid(-1, &status, 0) == last) && WIFEXITED(status))
			g_sig.exit_status = WEXITSTATUS(status);
		count++;
	}
}

void	exec_pipeline(t_vars *vars, t_ast *node, int ct)
{
	int		fdes[2];
	t_io	*io;

	io = &(vars->io);
	if (!ct)
		exec_first_pipe(io);
	else
	{
		set_flag(&(io->flag), PIPE_OUT);
		pipe(fdes);
		io->pipe[FD_OUT] = fdes[FD_OUT];
	}
	if (!fork())
	{
		exec_command(vars, node);
		exit(g_sig.exit_status);
	}
	close_handle(vars, node->data);
	if (ct)
		io->pipe[FD_IN] = fdes[FD_IN];
	vars->pipes_fd[(vars->nb_pipes)++] = io->pipe[FD_OUT];
	vars->pipes_fd[(vars->nb_pipes)++] = io->pipe[FD_IN];
}

void	exec_job(t_vars *vars, t_ast *node)
{
	parse_expansion(vars, node);
	if (check_flag(node->type, NODE_PIPE))
		fork_pipeline(vars, node);
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
