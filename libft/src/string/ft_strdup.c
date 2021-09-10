/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:13:14 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/29 18:10:29 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(sizeof(*dup) * (len + 1));
	if (!dup)
		return (dup);
	d = dup;
	while (len--)
		*d++ = *s++;
	*d = '\0';
	return (dup);
}
