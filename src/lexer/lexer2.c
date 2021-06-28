/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 05:14:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/17 20:34:34 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	job_token_handle(int tk_type, t_vars *vars, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	if ((tk_type == TK_GREAT) && (get_token_type(*(*buf + 1)) == TK_GREAT))
	{
		new_token(vars, TK_DGREAT, 0);
		(*buf)++;
	}
	else if ((tk_type == TK_LESS) && (get_token_type(*(*buf + 1)) == TK_LESS))
	{
		new_token(vars, TK_DLESS, 0);
		(*buf)++;
	}
	else
		new_token(vars, tk_type, 0);
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}

void	word_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (**buf);
	if (**buf == '\'')
		lexer->state = ST_QUOTE;
	else if (**buf == '\"')
		lexer->state = ST_DQUOTE;
}

void	space_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}

void	escape_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	if (*((*buf) + 1))
	{
		*(lexer->cur_char)++ = **buf;
		*(lexer->cur_char)++ = *(++(*buf));
	}
}

void	quote_handle(t_vars *vars, char *buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (*buf);
	if (((*buf == '\'') && (lexer->state == ST_QUOTE))
		|| ((*buf == '\"') && (lexer->state == ST_DQUOTE)))
		lexer->state = ST_GENERAL;
}
