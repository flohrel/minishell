/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_to_utf8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:13:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/02/19 10:17:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/conv.h"

static char	*fourbytes_utf(const uint32_t c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 4 + 1);
	ret[3] = (c & 0x3F) + 0x80;
	ret[2] = ((c & 0xFC0) >> 6) + 0x80;
	ret[1] = ((c & 0x3F000) >> 12) + 0x80;
	ret[0] = ((c & 0x1C0000) >> 18) + 0xF0;
	ret[4] = '\0';
	return (ret);
}

static char	*threebytes_utf(const uint32_t c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 3 + 1);
	ret[2] = (c & 0x3F) + 0x80;
	ret[1] = ((c & 0xFC0) >> 6) + 0x80;
	ret[0] = ((c & 0xF000) >> 12) + 0xE0;
	ret[3] = '\0';
	return (ret);
}

static char	*twobytes_utf(const uint32_t c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 2 + 1);
	ret[1] = (c & 0x3F) + 0x80;
	ret[0] = ((c & 0x7C0) >> 6) + 0xC0;
	ret[2] = '\0';
	return (ret);
}

static char	*onebyte_utf(const uint32_t c)
{
	char	*ret;

	ret = malloc(sizeof(char) * 1 + 1);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

char		*ft_uint_to_utf8(const uint32_t c)
{
	if (c < 0x80)
		return (onebyte_utf(c));
	else if (c < 0x800)
		return (twobytes_utf(c));
	else if (c < 0x10000)
		return (threebytes_utf(c));
	else
		return (fourbytes_utf(c));
}
