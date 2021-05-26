/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:56:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/26 23:41:05 by flohrel          ###   ########.fr       */
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
		*data = lst_alloc(len + 1, sizeof(*buffer), &vars->ptr_list);
		if (!(*data))
			clean_exit(vars, errno);
		ft_strlcpy(*data, buffer, len + 1);
	}
	else
	{
		delete_empty_token(&vars->lexer, &vars->parser);
		return (1);
	}
	return (0);
}

int		parse_word(t_vars *vars, t_lexer *lexer, char **data)
{
	char	buffer[BUFFER_SIZE];
	char	*str;
	int		index;

	index = 0;
	str = *data - 1;
	while (*(++str))
	{
		if (*str == '\'')
		{
			if (lexer->state == ST_GENERAL)
				lexer->state = ST_QUOTE;
			else
				lexer->state = ST_GENERAL;
		}
		else if (*str == '\\')
			buffer[index++] = *(++str);
		else if ((*str == '$') && (lexer->state != ST_QUOTE))
			var_expansion(buffer, &index, &str);
		else if ((*str != '\"') || (lexer->state == ST_QUOTE))
			buffer[index++] = *str;
	}
	buffer[index] = '\0';
	return (parse_word2(vars, data, buffer));
}

void	delete_empty_token(t_lexer *lexer, t_parser *parser)
{
	if (parser->prev_tk == NULL)
	{
		lexer->tk_list = lexer->tk_list->next;
		parser->cur_tk = lexer->tk_list;
	}
	else
	{
		parser->prev_tk->next = parser->cur_tk->next;
		parser->cur_tk = parser->prev_tk->next;
	}
}
