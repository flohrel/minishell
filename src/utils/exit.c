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

void	clean_exit(t_vars *vars, int status)
{
	free_ptr_lst(&vars->ptr_list);
	free_env(vars->env);
	free_env(vars->exp);
	free_env(vars->agn);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
