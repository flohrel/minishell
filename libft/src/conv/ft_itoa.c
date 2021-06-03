/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:58:12 by flohrel           #+#    #+#             */
/*   Updated: 2021/02/08 18:48:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/conv.h"

static char	*ft_itoa2(unsigned int n, size_t len, size_t idx,
		t_bool is_negative)
{
	char			*str;
	static size_t	i = 0;

	if (n < 10)
	{
		str = ft_calloc(len + 1, sizeof(*str));
		if (!str)
			return (str);
		str[len] = '\0';
		i = len;
		if (is_negative)
			str[idx + i++] = '-';
	}
	else
		str = ft_itoa2(n / 10, len + 1, idx - 1, is_negative);
	if (str)
		str[idx + i] = (n % 10) + '0';
	return (str);
}

char		*ft_itoa(int n)
{
	char			*str;
	static size_t	len = 0;
	static size_t	idx = 0;

	if (n < 0)
		str = ft_itoa2(-n, len + 2, idx - 2, TRUE);
	else
		str = ft_itoa2(n, len + 1, idx - 1, FALSE);
	len = 0;
	idx = 0;
	return (str);
}
