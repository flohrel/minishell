/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:03:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:57:25 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

static int	is_charset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*str;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	while (is_charset(*s1, set))
		s1++;
	start = s1;
	end = start;
	while (*s1)
	{
		if (!is_charset(*s1, set))
			end = s1 + 1;
		s1++;
	}
	len = end - start + 1;
	str = malloc(sizeof(*str) * len);
	if (!str)
		return (str);
	ft_strlcpy(str, start, len);
	return (str);
}
