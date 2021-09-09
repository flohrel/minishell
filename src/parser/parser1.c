/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 17:12:17 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/09 17:22:45 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	clean_empty_word(t_vars *vars, char **data, char *buffer)
{
	bool	has_quotes;
	size_t	len;

	has_quotes = false;
	if (ft_strchr(*data, '\'') || ft_strchr(*data, '\"'))
		has_quotes = true;
	if (*buffer || has_quotes)
	{
		len = ft_strlen(buffer);
		*data = lst_alloc(len + 1, sizeof(*buffer), vars);
		ft_strlcpy(*data, buffer, len + 1);
	}
	else
	{
		delete_empty_token(&vars->lexer, &vars->parser);
		return (1);
	}
	return (0);
}

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
