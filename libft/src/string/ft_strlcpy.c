/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:12:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 16:41:57 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	int			n;

	if (!dst || !src)
		return (0);
	n = size;
	s = src;
	if (n != 0)
	{
		while (--n)
		{
			*dst = *s++;
			if (*dst++ == '\0')
				break ;
		}
	}
	if (!n)
	{
		if (size != 0)
			*dst = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
