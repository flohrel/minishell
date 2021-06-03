/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 23:35:35 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:22:39 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/memory.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	tsize;
	size_t	maxsqrt;

	if ((SIZE_MAX / 641u / 6700417u) >= 4294967295u)
		maxsqrt = 65535;
	else
		maxsqrt = 4294967295;
	if (((nmemb > maxsqrt) || (size > maxsqrt))
		&& ((SIZE_MAX / nmemb) < size))
		return (NULL);
	tsize = nmemb * size;
	ptr = malloc(tsize);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, tsize);
	return (ptr);
}
