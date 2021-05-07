/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/08 01:45:23 by flohrel          ###   ########.fr       */
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

void	parse_word(t_vars *vars, t_lexer *lexer, char **data)
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
		else if (*str != '\"')
			buffer[index++] = *str;
	}
	buffer[index] = '\0';
	free(*data);
	*data = ft_strdup(buffer);
	if (*data == NULL)
		clean_exit(vars, 0);
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

int		syntax_error(char *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd(": quote missing", STDERR_FILENO);
	else
	{
		ft_putstr_fd("near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	return (-1);
}

int		parser(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token		*token;

	parser->cur_tk = lexer->tk_list;
	parser->prev_tk = NULL;
	if (lexer->state != ST_GENERAL)
		return (syntax_error(NULL));
	while (parser->cur_tk)
	{
		token = (t_token *)parser->cur_tk->content;
		if ((token->type < 0) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			if (token->type < 0)
				parse_word(vars, lexer, &token->data);
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	return (0);
}
