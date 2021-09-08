/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:03:22 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/08 12:54:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_token_list(t_lexer *lexer, t_parser *parser)
{
	t_token	*token;
	t_token	*prev;

	parser->cur_tk = lexer->tk_list;
	parser->prev_tk = NULL;
	while (parser->cur_tk)
	{
		token = (t_token *)parser->cur_tk->content;
		if (parser->prev_tk != NULL)
		{
			prev = (t_token *)parser->prev_tk->content;
			if ((prev->type == TK_DLESS) && (ft_strchr(token->data, '\'')
				|| ft_strchr(token->data, '\"')))
				prev->type = TK_DLESS2;
		}
		if ((token->type == TK_WORD) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
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
	return (node);
}

int	astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token	*token;

	clean_token_list(lexer, parser);
	display_token_list(&vars->lexer);									// TEST
	parser->cur_tk = lexer->tk_list;
	vars->exec_tree = list(vars, parser);
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_NL)
		return (syntax_error(token));
	return (0);
}
