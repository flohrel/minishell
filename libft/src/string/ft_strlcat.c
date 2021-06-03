/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:16:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:58:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		buf_size;
	int			dlen;
	char		*d;
	const char	*s;

	d = dst;
	buf_size = size;
	while (*d && buf_size--)
		d++;
	dlen = d - dst;
	buf_size = size - dlen;
	if (!buf_size)
		return (dlen + ft_strlen(src));
	s = src;
	while (*s)
	{
		if (buf_size != 1)
		{
			*d++ = *s;
			buf_size--;
		}
		s++;
	}
	*d = '\0';
	return (dlen + (s - src));
}
