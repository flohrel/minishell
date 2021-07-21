/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:05:59 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/12 11:41:15 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_b(char **args, t_vars *vars)
{
	if (check_flag(vars->cmd.io_bit, PIPE_IN))
		return (0);
	ft_putstr_fd("exit\n", 1);
	if (args && !(ft_strisdigit(args[0])))
		errormsg("exit : ", "argument must be a number");
	else if (ft_tablen(args) > 1)
		return (errormsg("exit : ", "too many arguments"));
	if (args && args[0])
		clean_exit(vars, NULL, ft_atoi(args[0]));
	else
		clean_exit(vars, NULL, 0);
	return (0);
}
