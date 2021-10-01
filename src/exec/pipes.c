/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:24:06 by mtogbe            #+#    #+#             */
/*   Updated: 2021/10/01 17:59:15 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	exec_last_pipe(t_vars *vars, t_ast *node)
{
	pid_t	pid;
	t_io	*io;

	io = &(vars->io);
	io->flag = -256;
	pid = fork();
	if (pid == 0)
	{
		exec_command(vars, node);
		exit(g_sig.exit_status);
	}
	close_handle(vars, node->data);
	return (pid);
}

void	exec_first_pipe(t_io *io)
{
	int		fdes[2];

	pipe(fdes);
	io->pipe[FD_OUT] = fdes[FD_OUT];
	io->pipe[FD_IN] = fdes[FD_IN];
	set_flag(&(io->flag), PIPE_IN);
}

void	clear_pipes(t_vars *vars, t_io *io)
{
	int	i;

	i = 0;
	if (is_pipe(io))
	{
		while (i < vars->nb_pipes)
		{
			close(vars->pipes_fd[i++]);
		}
		close(io->pipe[FD_OUT]);
		close(io->pipe[FD_IN]);
	}
}

int	pipe_handle(t_io *io)
{
	if (io->flag < 0)
		dup2(io->pipe[FD_IN], FD_IN);
	else if (check_flag(io->flag, PIPE_IN))
	{
		if (check_flag(io->flag, PIPE_IN))
			dup2(io->pipe[FD_OUT], FD_OUT);
		if (check_flag(io->flag, PIPE_OUT))
			dup2(io->pipe[FD_IN], FD_IN);
	}
	return (1);
}

int	close_handle(t_vars *vars, t_param *param)
{
	t_io	*gio;
	t_io	*io;

	gio = &vars->io;
	io = &param->io;
	if (gio->flag < 0)
		close(gio->pipe[FD_IN]);
	else if (check_flag(gio->flag, PIPE_IN))
	{
		if (check_flag(gio->flag, PIPE_IN))
			close(gio->pipe[FD_OUT]);
		if (check_flag(gio->flag, PIPE_OUT))
			close(gio->pipe[FD_IN]);
	}
	if (check_flag(io->flag, RD_IN))
		close(io->redir[FD_IN]);
	if (check_flag(io->flag, RD_OUT))
		close(io->redir[FD_OUT]);
	return (1);
}
