/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/06 05:54:57 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	free_vars(t_vars *vars)
{
	ft_lstclear(&vars->lexer.tk_list, del_token);
	if (vars->lexer.buffer)
		free(vars->lexer.buffer);
}

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	free_vars(vars);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
