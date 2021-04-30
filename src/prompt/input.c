/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 02:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/30 02:30:56 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		delete_handle(char *input, int *index)
{
	if (*index)
	{
		if (*(input - 1) == '\t')
			tputs(tgetstr("bt", NULL), 1, ft_putchar);
		else
			write(1, "\033[1D\033[0K", 8);
		(*index)--;
	}
	write(1, "\033[2D\033[0K", 8);
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
	if (size == 1)
	{
		if (*input == '\n')
			return (0);
		else if (*input == '\t')
			tputs(tgetstr("ta", NULL), 1, ft_putchar);
		else if (*input == 4)
			eot_handle(vars, index);
		else if (*input == 127)
			return (delete_handle(input, index));
		(*index)++;
	}
	return (1);
}

