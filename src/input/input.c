/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 02:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/30 18:26:12 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int		delete_handle(int *index)
{
	if (*index)
		(*index)--;
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
	return (1);
}

void	eot_handle(t_vars *vars, int *index)
{
	delete_handle(index);
	if (!(*index))
	{
		write(1, "exit\n", 5);
		clean_exit(vars, 0);
	}
}

// EN CHANTIER
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
	else if (*input == '\t')
		return (delete_handle(index));
	else if (*input == 127)
		return (delete_handle(index));
/*	else
	{
		if (*input == \033)
	}*/
	return (1);
}
