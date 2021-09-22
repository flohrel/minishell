/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:24:06 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/22 17:30:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	exec_last_pipe(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	pid_t	pid;

	cmd->io_bit = -256;
	g_sig.is_displayed = 0;
	pid = fork();
	if (pid == 0)
	{
		g_sig.is_child = 1;
		exec_command(vars, node);
		exit(g_sig.exit_status);
	}
	close(vars->cmd.pipe[FD_OUT]);
	close(vars->cmd.pipe[FD_IN]);
	return (pid);
}

void	exec_first_pipe(t_vars *vars, t_cmd *cmd, t_ast *node)
{
	int	fdes[2];

	(void)node;
	(void)vars;
	pipe(fdes);
	cmd->pipe[FD_OUT] = fdes[FD_OUT];
	cmd->pipe[FD_IN] = fdes[FD_IN];
	set_flag(&cmd->io_bit, PIPE_IN);
}

void	clear_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	if (is_pipe(vars))
	{
		while (i < vars->nb_pipes)
		{
			close(vars->pipes_fd[i++]);
		}
		close(vars->cmd.pipe[FD_OUT]);
		close(vars->cmd.pipe[FD_IN]);
	}
}	

int	pipe_handle(t_vars *vars)
{
	if (check_flag(vars->cmd.io_bit, RD_IN))
		return (1);
	if (check_flag(vars->cmd.io_bit, RD_OUT))
		return (1);
	ft_putstr_fd("pipe", 2);
	if (vars->cmd.io_bit < 0)
		vars->cmd.dup_in = dup2(vars->cmd.pipe[FD_IN], FD_IN);
	else if (check_flag(vars->cmd.io_bit, PIPE_IN))
	{
		if (check_flag(vars->cmd.io_bit, PIPE_IN))
			vars->cmd.dup_out = dup2(vars->cmd.pipe[FD_OUT], FD_OUT);
		if (check_flag(vars->cmd.io_bit, PIPE_OUT))
			vars->cmd.dup_in = dup2(vars->cmd.pipe[FD_IN], FD_IN);
	}
	return (1);
}

int	close_handle(t_vars *vars)
{
	if (vars->cmd.io_bit < 0)
		close(vars->cmd.pipe[FD_IN]);
	else if (check_flag(vars->cmd.io_bit, PIPE_IN))
	{
		if (check_flag(vars->cmd.io_bit, PIPE_IN))
			close(vars->cmd.pipe[FD_OUT]);
		if (check_flag(vars->cmd.io_bit, PIPE_OUT))
			close(vars->cmd.pipe[FD_IN]);
	}
	if (check_flag(vars->cmd.io_bit, FD_IN))
		close(vars->cmd.redir[FD_IN]);
	if (check_flag(vars->cmd.io_bit, FD_OUT))
		close(vars->cmd.redir[FD_OUT]);
	return (1);
}
