/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:36:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:57:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*str;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size < start)
		size = 0;
	else
		size -= start;
	if (size < len)
		len = size;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
