/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/29 18:52:25 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	ft_lstclear(&vars->lexer.tokens, del_token);
	if (vars->lexer.buffer)
		free(vars->lexer.buffer);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
