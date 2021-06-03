/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:20:33 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:52:38 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/conv.h"

static int	check_overflow(unsigned int nb, int nptr, int sign)
{
	unsigned int n;

	if (sign > 0)
		n = (INT_MAX - nptr + '0') / 10;
	else
		n = -(INT_MIN + nptr - '0') / 10;
	if (nb > n)
		return (1);
	return (0);
}

int			ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (((*nptr == '-') || (*nptr == '+')) &&
		(*nptr++ == '-'))
		sign = -sign;
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		if (check_overflow(nb, *nptr, sign))
			return (0);
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (sign * nb);
}
