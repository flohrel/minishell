/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 00:50:37 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:58:49 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*end;

	end = s + ft_strlen(s);
	while (s <= end)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
