/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/07 17:17:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_word(t_vars *vars, char *string)
{
	(void)vars;
	(void)string;
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
				parse_word(vars, token->data);
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	return (0);
}
