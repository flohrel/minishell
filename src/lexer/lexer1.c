/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 05:14:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/10 18:00:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	redirection_handle(t_vars *vars, int tk_type, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	if (check_flag(tk_type, TK_GREAT)
		&& (get_token_type(*(*buf + 1)) == (TK_GREAT | TK_REDIR)))
	{
		new_token(vars, TK_DGREAT | TK_REDIR, 0);
		(*buf)++;
	}
	else if (check_flag(tk_type, TK_LESS)
		&& (get_token_type(*(*buf + 1)) == (TK_LESS | TK_REDIR)))
	{
		new_token(vars, TK_DLESS | TK_REDIR, 0);
		(*buf)++;
	}
	else
		new_token(vars, tk_type, 0);
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}

void	job_handle(t_vars *vars, int tk_type, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	if (check_flag(tk_type, TK_PIPE)
		&& (get_token_type(*(*buf + 1)) == TK_PIPE))
	{
		new_token(vars, TK_DPIPE | TK_LIST, 0);
		(*buf)++;
	}
	else if (check_flag(tk_type, TK_AMP)
		&& (get_token_type(*(*buf + 1)) == TK_AMP))
	{
		new_token(vars, TK_DAMP | TK_LIST, 0);
		(*buf)++;
	}
	else
		new_token(vars, tk_type, 0);
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}

void	compound_handle(t_vars *vars, int tk_type, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	new_token(vars, tk_type, 0);
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}

void	word_handle(t_vars *vars, int tk_type, char **buf)
{
	t_lexer	*lexer;

	(void)tk_type;
	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (**buf);
	if (**buf == '\'')
		lexer->esc_st = ST_QUOTE;
	else if (**buf == '\"')
		lexer->esc_st = ST_DQUOTE;
}

void	space_handle(t_vars *vars, int tk_type, char **buf)
{
	t_lexer	*lexer;
	int		size;

	(void)tk_type;
	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TK_WORD, size);
}
