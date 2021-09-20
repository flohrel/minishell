/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 21:07:55 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/08 17:57:18 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

static char	*str_concat(char *dest, char *src, const char *sep, int wcount)
{
	char	*tmp;

	tmp = dest;
	while (*tmp)
		tmp++;
	while (*src)
	{
		*tmp = *src;
		tmp++;
		src++;
	}
	if (wcount && sep)
	{
		while (*sep)
		{
			*tmp = *sep;
			tmp++;
			sep++;
		}
	}
	*tmp = '\0';
	return (dest);
}

char	*ft_strsjoin(int size, char **strs, const char *sep)
{
	static int	len = 0;
	static int	wcount = 0;
	static char	*str = NULL;

	if (!size)
	{
		if (wcount)
			len += (ft_strlen(sep) * (wcount - 1));
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		*str = '\0';
		return (str);
	}
	wcount++;
	len += ft_strlen(strs[size - 1]);
	str = ft_strsjoin(size - 1, strs, sep);
	str = str_concat(str, strs[size - 1], sep, --wcount);
	return (str);
}
