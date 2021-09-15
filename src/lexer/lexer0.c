/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/15 22:03:28 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quote_handle(t_vars *vars, char *buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (*buf);
	if (((*buf == '\'') && (lexer->esc_st == ST_QUOTE))
		|| ((*buf == '\"') && (lexer->esc_st == ST_DQUOTE)))
		lexer->esc_st = ST_GENERAL;
}

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	lexer->esc_st = ST_GENERAL;
	lexer->buf_len = ft_strlen(lexer->buffer);
	new_token(vars, TK_WORD, lexer->buf_len);
}

void	token_handle(t_vars *vars, int tk_type, char **buffer)
{
	if (check_flag(tk_type, TK_REDIR))
		redirection_handle(vars, tk_type, buffer);
	else if (check_flag(tk_type, TK_COMPND))
		compound_handle(vars, tk_type, buffer);
	else if (check_flag(tk_type, TK_PIPE) || check_flag(tk_type, TK_AMP))
		job_handle(vars, tk_type, buffer);
	else if (tk_type == TK_SPACE)
		space_handle(vars, tk_type, buffer);
	else
		word_handle(vars, tk_type, buffer);
}

int	lexer(t_vars *vars, t_lexer *lexer)
{
	char	*buffer;
	int		tk_type;

	lexer_init(vars);
	buffer = lexer->buffer;
	while (*buffer)
	{
		tk_type = get_token_type(*buffer);
		if (lexer->esc_st == ST_GENERAL)
			token_handle(vars, tk_type, &buffer);
		else
			quote_handle(vars, buffer);
		buffer++;
	}
	if (lexer->esc_st != ST_GENERAL)
		return (syntax_error(NULL));
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	new_token(vars, TK_NL, 0);
	return (0);
}
