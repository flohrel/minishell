/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:56:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/30 18:31:39 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_charset(const char *charset, char c)
{
	while (*charset)
	{
		if (c == *charset || !c)
			return (1);
		charset++;
	}
	return (0);
}

void	var_expansion(char *buffer, int *index, char **data)
{
	char	*var;
	int		size;
	char	*str;
	char	tmp;

	str = *data;
	while (*(str++))
	{
		if (is_charset("\'\" ", *str))
		{
			tmp = *str;
			*str = '\0';
			var = getenv(*data + 1);
			*str = tmp;
			*data = str - 1;
			break ;
		}
	}
	size = ft_strlen(var);
	ft_strlcpy(&buffer[*index], var, size + 1);
	(*index) += size;
}

int		parse_word2(t_vars *vars, char **data, char *buffer)
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

void	parse_word1(int state, char *str, char *buffer, int *index)
{
	if (*str == '\'' && state != ST_DQUOTE)
	{
		if (state == ST_GENERAL)
			state = ST_QUOTE;
		else
			state = ST_GENERAL;
	}
	else if (*str == '\"' && state != ST_QUOTE)
	{
		if (state == ST_GENERAL)
			state = ST_DQUOTE;
		else
			state = ST_GENERAL;
	}
	else if (*str == '\\')
		buffer[(*index)++] = *(++str);
	else if ((*str == '$') && (state != ST_QUOTE))
		var_expansion(buffer, index, &str);
	else
		buffer[(*index)++] = *str;
}

int		parse_word(t_vars *vars, t_lexer *lexer, char **data)
{
	char	buffer[BUFFER_SIZE];
	char	*str;
	int		index;

	index = 0;
	str = *data - 1;
	while (*(++str))
		parse_word1(lexer->state, str, buffer, &index);
	buffer[index] = '\0';
	return (parse_word2(vars, data, buffer));
}
