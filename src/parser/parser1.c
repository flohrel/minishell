/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:12:17 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/15 14:11:31 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	path_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	char	*s;
	char	*buf;
	int		state;
	bool	has_changed;

	s = str;
	buf = buffer;
	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		has_changed = state_check(&state, c);
		if ((c == '*') && (state == ST_GENERAL))
		{
			wildcard(vars, buf, s);
			return ;
		}
		else if (has_changed == false)
			*buffer++ = c;
		str++;
	}
	*buffer = '\0';
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
		if ((c == '$') && (state != ST_QUOTE) && (*(str + 1) != '\0'))
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
			*buffer++ = c;
		str++;
	}
	*buffer = '\0';
}
