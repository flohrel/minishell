/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:03:22 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/03 18:04:30 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_token_list(t_lexer *lexer, t_parser *parser)
{
	t_token		*token;

	parser->cur_tk = lexer->tk_list;
	parser->prev_tk = NULL;
	while (parser->cur_tk)
	{
		token = (t_token *)parser->cur_tk->content;
		if ((token->type == TK_WORD) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
}

int	astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token	*token;

	clean_token_list(lexer, parser);
	parser->cur_tk = lexer->tk_list;
	vars->exec_tree = list(vars, parser);
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_NL)
		return (syntax_error(token));
	return (0);
}
