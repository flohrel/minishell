/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:58:12 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/10 13:20:08 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/conv.h"

static char	*ft_ltoa2(uint64_t n, size_t len, size_t idx, bool is_negative)
{
	char		*str;
	static int	l = 0;

	if (n < 10)
	{
		str = ft_calloc(len + 1, sizeof(*str));
		if (!str)
			return (str);
		str[len] = '\0';
		l = len;
		if (is_negative)
			str[idx + l++] = '-';
	}
	else
		str = ft_ltoa2(n / 10, len + 1, idx - 1, is_negative);
	if (str)
		str[idx + l] = (n % 10) + '0';
	return (str);
}

char	*ft_ltoa(int64_t n)
{
	char			*str;
	static size_t	len = 0;
	static size_t	idx = 0;

	if (n < 0)
		str = ft_ltoa2(-n, len + 2, idx - 2, true);
	else
		str = ft_ltoa2(n, len + 1, idx - 1, false);
	len = 0;
	idx = 0;
	return (str);
}
