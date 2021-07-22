/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/21 16:01:48 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_unlisted_vars(t_vars *vars)
{
	(void)vars;
}

void	clean_exit(t_vars *vars, char *arg, int status)
{
	int		ret_val;

	ret_val = 0;
	if (errno)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		if (arg)
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	if (status)
		ret_val = status;
	free_ptr_lst(&vars->ptr_list);
	free_unlisted_vars(vars);
	free_env(vars->env);
	free_env(vars->exp);
	free_env(vars->agn);
	rl_clear_history();
	exit(ret_val);
}
