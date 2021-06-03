/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:53:02 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:56:25 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char ch;

	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*str == ch)
			return (str);
		++str;
	}
	return (NULL);
}
