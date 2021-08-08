/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:03:22 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/08 21:03:40 by flohrel          ###   ########.fr       */
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
