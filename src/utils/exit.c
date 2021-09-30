/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/16 17:52:17 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	clean_exit(t_vars *vars, char *arg, char *err_msg, int status)
{
	if (errno && (errno != EINTR) && (errno != EBADF))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (arg)
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		if (err_msg)
			ft_putstr_fd(err_msg, STDERR_FILENO);
		else
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	free_ptr_lst(&vars->ptr_list);
	free_env(vars->env);
	free_env(vars->exp);
	free_env(vars->agn);
	rl_clear_history();
	exit(status + 127);
}
