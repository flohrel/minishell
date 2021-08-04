/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:03:51 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:46:11 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*str;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	while (is_charset(set, *s1))
		s1++;
	start = s1;
	end = start;
	while (*s1)
	{
		if (!is_charset(set, *s1))
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
