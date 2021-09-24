/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:24:06 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/24 17:22:40 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	exec_last_pipe(t_vars *vars, t_ast *node, t_io *io)
{
	pid_t	pid;

	io->flag = -256;
	g_sig.is_displayed = 0;
	pid = fork();
	if (pid == 0)
	{
		g_sig.is_child = 1;
		exec_command(vars, node);
		exit(g_sig.exit_status);
	}
	close(io->pipe[FD_OUT]);
	close(io->pipe[FD_IN]);
	return (pid);
}

void	exec_first_pipe(t_ast *node)
{
	int		fdes[2];
	t_io	*io;

	io = &(node->data->io);
	pipe(fdes);
	io->pipe[FD_OUT] = fdes[FD_OUT];
	io->pipe[FD_IN] = fdes[FD_IN];
	set_flag(&(io->flag), PIPE_IN);
}

void	clear_pipes(t_io *io)
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
		io->dup_in = dup2(io->pipe[FD_IN], FD_IN);
	else if (check_flag(io->flag, PIPE_IN))
	{
		if (check_flag(io->flag, PIPE_IN))
			io->dup_out = dup2(io.pipe[FD_OUT], FD_OUT);
		if (check_flag(io->flag, PIPE_OUT))
			io->dup_in = dup2(io->pipe[FD_IN], FD_IN);
	}
	return (1);
}

int	close_handle(t_io *io)
{
	if (io->flag < 0)
		close(io->pipe[FD_IN]);
	else if (check_flag(io->flag, PIPE_IN))
	{
		if (check_flag(io->flag, PIPE_IN))
			close(io->pipe[FD_OUT]);
		if (check_flag(io->flag, PIPE_OUT))
			close(io->pipe[FD_IN]);
	}
	if (check_flag(io->flag, FD_IN))
		close(io->redir[FD_IN]);
	if (check_flag(io->flag, FD_OUT))
		close(io->redir[FD_OUT]);
	return (1);
}
