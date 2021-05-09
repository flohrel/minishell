/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:56:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/09 18:49:03 by flohrel          ###   ########.fr       */
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
		if (is_charset("\" ", *str))
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

	has_quotes = false;
	if (ft_strchr(*data, '\'') || ft_strchr(*data, '\"'))
		has_quotes = true;
	if (*buffer || has_quotes)
	{
		free(*data);
		*data = ft_strdup(buffer);
		if (*data == NULL)
			clean_exit(vars, 0);
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
		ft_lstdelone(parser->cur_tk, del_token);
		parser->cur_tk = lexer->tk_list;
	}
	else
	{
		parser->prev_tk->next = parser->cur_tk->next;
		ft_lstdelone(parser->cur_tk, del_token);
		parser->cur_tk = parser->prev_tk->next;
	}
}
