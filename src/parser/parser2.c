/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:56:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/01 02:34:08 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*var_assignation(t_vars *vars, char *data, char *str)
{
	char	*var;
	char	tmp;

	tmp = *str;
	*str = '\0';
	var = get_env_value(data, vars->env);
	if (!var)
	{
		var = ft_strdup("\0");
		if (!var)
			return (NULL);
		add_to_ptrlst((void *)var, vars);
	}
	*str = tmp;
	return (var);
}

void	var_expansion(t_vars *vars, char **buffer, char **data)
{
	char	*var;
	char	*str;

	str = *data;
	if (*(str + 1) == '?')
		var = ft_itoa(vars->exit_status);
	else
	{
		while (*(str++))
		{
			if (!(*str) || (!ft_isalnum(*str) && (*str != '_')))
			{
				var = var_assignation(vars, *data + 1, str);
				if (!var)
					clean_exit(vars, 127);
				break ;
			}
		}
	}
	ft_strlcpy(*buffer, var, ft_strlen(var) + 1);
	if (ft_strlen(var))
		(*buffer) += ft_strlen(var) - 1;
	(*data) = str - 1;
}

int	parse_word2(t_vars *vars, char **data, char *buffer)
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

void	parse_word1(t_vars *vars, int *state, char **str, char **buffer)
{
	char	c;

	c = **str;
	if ((c == '\'') && (*state != ST_DQUOTE))
	{
		if (*state == ST_GENERAL)
			*state = ST_QUOTE;
		else
			*state = ST_GENERAL;
	}
	else if ((c == '\"') && (*state != ST_QUOTE))
	{
		if (*state == ST_GENERAL)
			*state = ST_DQUOTE;
		else
			*state = ST_GENERAL;
	}
	else if ((c == '\\') && (*state != ST_QUOTE)
		&& ((*state == ST_GENERAL) || is_charset("$`\"\\", *((*str) + 1))))
		*(*buffer)++ = *(++(*str));
	else if ((c == '$') && (*state != ST_QUOTE))
		var_expansion(vars, buffer, str);
	else
		*(*buffer)++ = c;
}

int	parse_word(t_vars *vars, char **data)
{
	char	buffer[BUFFER_SIZE];
	char	*ptr;
	char	*str;

	str = *data;
	ptr = buffer;
	while (*str)
	{
		parse_word1(vars, &vars->lexer.state, &str, &ptr);
		str++;
	}
	*ptr = '\0';
	return (parse_word2(vars, data, buffer));
}
