/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_charset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:51:46 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/05 19:53:42 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	is_charset(const char *set, char c)
{
	if (set)
	{
		while (*set)
		{
			if (c == *set)
				return (1);
			set++;
		}
	}
	return (0);
}
