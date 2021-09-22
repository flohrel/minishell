/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:03:22 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/20 17:12:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_node_type(t_parser *parser)
{
	if (check_token(parser, (TK_DAMP | TK_LIST)))
		return (NODE_AND | NODE_LIST);
	if (check_token(parser, (TK_DPIPE | TK_LIST)))
		return (NODE_OR | NODE_LIST);
	return (0);
}

t_ast	*list(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_list	*save;

	save = parser->cur_tk;
	node = list1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = list2(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = list3(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = job(vars, parser);
	return (node);
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
