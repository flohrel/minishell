/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_already.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:22:32 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 04:22:34 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_already(char *str, int index, char c)
{
	int	i;

	i = 0;
	while (str[i] && i < index)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
