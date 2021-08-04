/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:36:45 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:56:12 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		idx;
	int		i;

	if (!dest || !src)
		return (dest);
	s = (char *)src;
	d = (char *)dest;
	idx = 0;
	i = 1;
	if (d > s)
	{
		idx = n - 1;
		i = -1;
	}
	while (n--)
	{
		d[idx] = s[idx];
		idx += i;
	}
	return (dest);
}
