/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:58:34 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/06 12:48:28 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	get_token_char(int type)
{
	if (type == TK_PIPE)
		return ('|');
	else if (type == TK_AMP)
		return ('&');
	else if (type == TK_QUOTE)
		return ('\'');
	else if (type == TK_DQUOTE)
		return ('\"');
	else if (type == TK_GREAT)
		return ('>');
	else if (type == TK_LESS)
		return ('<');
	else if (type == TK_SPACE)
		return (' ');
	else
		return (0);
}

int	get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == '&')
		return (TK_AMP);
	else if (c == '\'')
		return (TK_QUOTE);
	else if (c == '\"')
		return (TK_DQUOTE);
	else if (c == '>')
		return (TK_GREAT);
	else if (c == '<')
		return (TK_LESS);
	else if (c == ' ')
		return (TK_SPACE);
	else
		return (TK_WORD);
}

void	new_token(t_vars *vars, int type, int size)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*lst;

	lexer = &vars->lexer;
	token = lst_alloc(1, sizeof(*token), vars);
	token->type = type;
	token->data = NULL;
	lexer->cur_char = NULL;
	if (size)
	{
		token->data = lst_alloc(size + 1, sizeof(char), vars);
		lexer->cur_char = token->data;
	}
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->content = token;
	lst->next = NULL;
	ft_lstadd_back(&lexer->tk_list, lst);
}

void	delete_empty_token(t_lexer *lexer, t_parser *parser)
{
	if (parser->prev_tk == NULL)
	{
		lexer->tk_list = lexer->tk_list->next;
		parser->cur_tk = lexer->tk_list;
	}
	else
	{
		parser->prev_tk->next = parser->cur_tk->next;
		parser->cur_tk = parser->prev_tk->next;
	}
}
