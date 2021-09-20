/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:23:52 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/15 13:21:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*clear_quotes(char *str)
{
	int		state;
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	state = ST_GENERAL;
	result = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (!state_check(&state, str[i]))
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	replace_cpy(char *dst, char **replace, int i)
{
	int	j;
	int	k;

	j = 0;
	dst[i++] = 127;
	while (replace[j])
	{
		k = 0;
		while (replace[j][k])
			dst[i++] = replace[j][k++];
		if (replace[j + 1])
			dst[i++] = ' ';
		j++;
	}
	dst[i++] = 127;
	dst[i] = '\0';
}

char	*ft_replace(char *dst, char **replace)
{
	int	i;

	i = 0;
	dst[i] = '\0';
	replace_cpy(dst, replace, i);
	return (dst);
}
