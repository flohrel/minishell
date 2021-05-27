/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 18:40:46 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	parser->cur_tk = lexer->tk_list;
	parser->exec_tree = cmdline(vars, parser);
	if (parser->exec_tree == NULL)
		return (syntax_error(parser->cur_tk->content));
	return (0);
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
		if ((token->type == TK_WORD) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			if ((token->type == TK_WORD) &&
				parse_word(vars, lexer, &token->data))
				continue ;
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	display_token_list(&vars->lexer);						// TEST
	return (astree_build(vars, lexer, parser));
}
