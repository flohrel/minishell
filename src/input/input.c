/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 02:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/02 19:03:57 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		delete_handle(int *index)
{
	if (*index)
	{
		(*index)--;
		write(2, "\033[1D", 4);
		write(2, "\033[0K", 4);
	}
	write(2, "\033[2D\033[0K", 8);
	return (-1);
}

void	eot_handle(t_vars *vars, int *index)
{
	write(1, "\033[2D\033[0K", 8);
	if (!(*index))
	{
		write(1, "exit\n", 5);
		clean_exit(vars, 0);
	}
}

int		input_handle(t_vars *vars, char *input, int size, int *index)
{
	(void)size;
	if (*input == '\n')
	{
		*input = '\0';
		return (0);
	}
	else if (*input == 4)
		eot_handle(vars, index);
	else if (*input < '\040')
	{
/*
		if (input[2] == 'D')
				tputs(tgetstr("le", NULL), 1, ft_putchar);
			else if (input[2] == 'C')
				tputs(tgetstr("nd", NULL), 1, ft_putchar);
			else if (input[2] == 'A')
				REMONTER HISTORIQUE
			else if (input[2] == 'B')
				DESCENDRE HISTORIQUE
*/
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
	}
	else if (*input == 127)
		return (delete_handle(index));
	else
		(*index)++;
	return (1);
}
