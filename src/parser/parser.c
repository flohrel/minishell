/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/22 22:33:14 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token	*token;

	parser->cur_tk = lexer->tk_list;
	parser->exec_tree = list(vars, parser);
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_NL)
		return (syntax_error(token));
	return (0);
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
	else if ((c == '$') && (*state != ST_QUOTE) && (*((*str) + 1) != '\0'))
		var_expansion(vars, buffer, str);
	else
		*(*buffer)++ = c;
}

int	parse_word0(t_vars *vars, char **data)
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

int	parser(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token		*token;

	parser->cur_tk = lexer->tk_list;
	parser->prev_tk = NULL;
	if (lexer->state != ST_GENERAL)
		return (syntax_error(NULL));
	while (parser->cur_tk)
	{
		token = (t_token *)parser->cur_tk->content;
		if ((token->type == TK_WORD) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			if ((token->type == TK_WORD)
				&& parse_word0(vars, &token->data))
				continue ;
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	if (lexer->state != ST_GENERAL)
		return (syntax_error(NULL));
	return (astree_build(vars, lexer, parser));
}
