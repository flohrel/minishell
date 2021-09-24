/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:05:59 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/24 17:01:44 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_pipe(t_io *io)
{
	if ((io->flag < 0) || check_flag(io->flag, PIPE_IN))
		return (1);
	return (0);
}

int	exit_b(char **args, t_vars *vars, t_param *param)
{
	if (!is_pipe(&(param->io)))
		ft_putstr_fd("exit", 2);
	if (args && !(ft_strisdigit(args[0])))
	{
		if (!is_pipe(&(param->io)))
			ft_putstr_fd("\n", 2);
		path_error("exit: ", args[0]);
		ft_putstr_fd(": argument must be a number", 2);
		if (!is_pipe(&(param->io)))
			clean_exit(vars, NULL, NULL, 2 - 127);
		else
			ft_putstr_fd("\n", 2);
	}
	else if (ft_tablen(args) > 1)
		return (errormsg("\nminishell: exit : ",
				"too many arguments"));
	if (args && args[0] && !is_pipe(&(param->io)))
		clean_exit(vars, NULL, NULL, ft_atoi(args[0]) - 127);
	else if (!is_pipe(&(param->io)))
		clean_exit(vars, NULL, NULL, -127);
	else if (args && args[0])
		return (ft_atoi(args[0]));
	return (0);
}
