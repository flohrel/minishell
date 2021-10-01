/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:22:59 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 04:23:36 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] && (str[i] == '-' || str[i] == '+') && str[i + 1])
		i++;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
