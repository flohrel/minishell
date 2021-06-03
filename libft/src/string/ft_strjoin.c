/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:35:57 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:58:40 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	tlen;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((SIZE_MAX - len1 - 1) < len2 ||
		(SIZE_MAX - len2 - 1) < len1)
		return (NULL);
	tlen = len1 + len2 + 1;
	str = malloc(sizeof(*str) * tlen);
	if (!str)
		return (str);
	*str = '\0';
	ft_strlcat(str, s1, len1 + 1);
	ft_strlcat(str, s2, tlen);
	return (str);
}
