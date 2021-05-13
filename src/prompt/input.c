/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 02:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/13 18:11:46 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		delete_handle(char *input, int *index)
{
	(void)input;
	if (*index)
	{
// A supprimer
		if (*(input - 1) == '\t')
			tputs(tgetstr("bt", NULL), 1, ft_putchar);
//
		write(1, "\033[1D\033[0K", 8);
		(*index)--;
	}
	write(1, "\033[2D\033[0K", 8);
	return (-1);
}

// Inutile car traitee dans input_handler ?
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
		{
			*input = '\0';
			return (0);
		}
// A supprimer
		else if (*input == '\t')
			tputs(tgetstr("ta", NULL), 1, ft_putchar);
//
		else if (*input == 4)
			eot_handle(vars, index);
		else if (*input == 127)
			return (delete_handle(input, index));
		(*index)++;
	}
	return (1);
}
