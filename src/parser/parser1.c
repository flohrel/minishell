/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:12:17 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/01 18:26:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	path_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	char	*s;
	char	*buf;
	int		state;

	s = str;
	buf = buffer;
	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		state_check(&state, c);
		if ((c == '*') && (state == ST_GENERAL))
		{
			wildcard(vars, buffer, s);
			return ;
		}
		*buf = c;
		buf++;
		str++;
	}
	*buf = '\0';
}

void	param_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	int		state;

	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		state_check(&state, c);
		if ((c == '$') && (state != ST_QUOTE)
			&& !ft_ischarset(*(str + 1), "\0="))
			var_expansion(vars, &buffer, &str);
		else
		{
			*buffer = c;
			buffer++;
		}
		str++;
	}
	*buffer = '\0';
}

void	delete_quote(char *str, char *buffer)
{
	char	c;
	int		state;

	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		if (state_check2(&state, c) == false)
		{
			*buffer = c;
			buffer++;
		}
		str++;
	}
	*buffer = '\0';
}
