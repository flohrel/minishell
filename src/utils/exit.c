/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 12:59:07 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	del_hist_entry(void *content)
{
	free(content);
}

void	free_unlisted_vars(t_vars *vars)
{
	ft_dlstclear(&vars->history.lst, del_hist_entry);
}

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	free_ptr_lst(&vars->ptr_list);
	free_unlisted_vars(vars);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
