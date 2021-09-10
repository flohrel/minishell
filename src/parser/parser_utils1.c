/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:39:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/10 16:40:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

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
