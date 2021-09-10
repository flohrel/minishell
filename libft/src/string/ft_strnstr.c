/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 03:51:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:48:58 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lsize;

	lsize = ft_strlen(little);
	if (!lsize)
		return ((char *)big);
	if (len)
	{
		len -= (lsize - 1);
		if (len > 0)
		{
			while (len-- && *big)
			{
				if (!ft_strncmp(big, little, lsize))
					return ((char *)big);
				big++;
			}
		}
	}
	return (NULL);
}
