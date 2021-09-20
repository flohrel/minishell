/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:05:59 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/16 17:32:48 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_b(char **args, t_vars *vars)
{
	if (check_flag(vars->cmd.io_bit, PIPE_IN))
		return (0);
	ft_putstr_fd("exit", 1);
	if (args && !(ft_strisdigit(args[0])))
	{
		ft_putstr_fd("\n", 2);
		path_error("exit: ", args[0]);
		ft_putstr_fd(": argument must be a number", 2);
		clean_exit(vars, NULL, NULL, 2 - 127);
	}
	else if (ft_tablen(args) > 1)
		return (errormsg("\nminishell: exit : ",
				"too many arguments"));
	if (args && args[0])
		clean_exit(vars, NULL, NULL, ft_atoi(args[0]) - 127);
	else
		clean_exit(vars, NULL, NULL, -127);
	return (0);
}
