/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/17 18:55:31 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_unlisted_vars(t_vars *vars)
{
	(void)vars;
}

void	clean_exit(t_vars *vars, int status)
{
	int		ret_val;

	free_ptr_lst(&vars->ptr_list);
	free_unlisted_vars(vars);
	free_env(vars->env);
	free_env(vars->exp);
	free_env(vars->agn);
	if (errno)
		printf("minishell: %s\n", strerror(errno));
	if (!status)
		ret_val = 0;
	else
		ret_val = 128 + status;
	exit(ret_val);
}
