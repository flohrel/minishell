/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/03 17:51:32 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
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

	s = str;
	buf = buffer;
	(void)vars;
	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		state_check(&state, c);
		if ((c == '*') && (state == ST_GENERAL))
		{
			wildcard(vars, buf, s);
			return ;
		}
		else
		{
			*buffer = c;
			buffer++;
		}
		str++;
	}
	*buffer = '\0';
}

void	param_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	char	*s;
	char	*buf;
	int		state;

	buf = buffer;
	s = str;
	state = ST_GENERAL;
	while (*s)
	{
		c = *s;
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

int	parse_word(t_vars *vars, t_list *prev_tk, char *data)
{
	t_token	*token;
	char	buffer[2][BUFFER_SIZE];

	if (prev_tk != NULL)
	{
		token = (t_token *)prev_tk->content;
		if ((token->type == TK_DLESS) && (ft_strchr(*data, '\'')
				|| ft_strchr(*data, '\"')))
			token->type = TK_DLESS2;
	}
	param_expansion(vars, *data, buffer[0]);
	path_expansion(vars, buffer[0], buffer[1]);
	return (clean_empty_word(vars, data, buffer[1]));
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
				&& parse_word(vars, parser->prev_tk, token->data))
				continue ;
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	if (lexer->state != ST_GENERAL)
		return (syntax_error(NULL));
	return (astree_build(vars, lexer, parser));
}*/
