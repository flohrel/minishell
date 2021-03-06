/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:27:25 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/21 03:48:33 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	set_flag(int *field, int flag)
{
	return ((*field) |= flag);
}

int	check_flag(int field, int flag)
{
	return (field & flag);
}

void	clear_flag(int *field, int flag)
{
	(*field) &= ~(flag);
}
