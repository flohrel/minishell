/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 07:54:20 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	free_ptr_lst(&vars->ptr_list);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
