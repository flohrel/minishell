/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 04:59:07 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		syntax_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd(": quote missing\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(" near unexpected token `", STDERR_FILENO);
		if (token->type == TK_NL)
			ft_putstr_fd("newline", STDERR_FILENO);
		else if (token->type == TK_DGREAT)
			ft_putstr_fd(">>", STDERR_FILENO);
		else
			ft_putchar_fd(get_token_char(token->type), STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
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
	return (astree_build(vars, lexer, parser));
}
