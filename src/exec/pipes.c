/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:24:06 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/16 17:27:01 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	add_pipe(t_vars *vars, t_ast *node)
{
	t_pipes	*tmp;

	tmp = vars->pipes;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_pipes));
		if (tmp->next)
			return (-1);
		tmp->next->p_open = 1;
		tmp->next->node = node;
		tmp->next->prev = tmp;
	}
	else
	{
		tmp->next = malloc(sizeof(t_pipes));
		if (tmp->next)
			return (-1);
	}
	return (1);
}

int	pipe_handle(t_vars *vars)
{
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
