/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:52:36 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:53:11 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"

static char	*ft_strndup(char *s, size_t len)
{
	char	*d;
	char	*dup;

	dup = malloc(sizeof(*dup) * (len + 1));
	if (!dup)
		return (dup);
	d = dup;
	while (len--)
		*d++ = *s++;
	*d = '\0';
	return (dup);
}

static char	**sstr_alloc(size_t tlen)
{
	char	**sstr;

	sstr = malloc(sizeof(*sstr) * (tlen + 1));
	if (sstr)
		sstr[tlen] = NULL;
	return (sstr);
}

static char	**str_alloc(char **sstr, size_t *tlen, char *s, size_t len)
{
	(*tlen)--;
	sstr[*tlen] = ft_strndup((char *)s, len);
	if (!sstr[*tlen])
	{
		while (sstr[*tlen])
		{
			free(sstr[*tlen]);
			(*tlen)++;
		}
		*tlen = 0;
		return (NULL);
	}
	return (sstr);
}

char	**ft_split(char const *s, char c)
{
	char			**sstr;
	const char		*sptr;
	static size_t	tlen = 0;

	if (!s)
		return (NULL);
	sptr = (char *)s;
	while (1)
	{
		if ((*sptr == c) || !(*sptr))
		{
			if (sptr - s)
			{
				tlen++;
				sstr = ft_split(sptr, c);
				if (sstr)
					sstr = str_alloc(sstr, &tlen, (char *)s, sptr - s);
				return (sstr);
			}
			if (!(*sptr))
				return (sstr_alloc(tlen));
			return (ft_split(sptr + 1, c));
		}
		sptr++;
	}
}
