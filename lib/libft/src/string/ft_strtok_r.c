/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 20:47:45 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/07 22:17:13 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

static int	is_charset(const char *charset, char c)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

char		*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char		*start;

	start = str;
	while (*str)
	{
		if (is_charset(delim, *str) && ((str - start) > 0))
		{
			*str = '\0';
			*saveptr = str + 1;
			return (start);
		}
		str++;
	}
	*saveptr = str;
	if (str - start)
		return (start);
	return (NULL);
}
