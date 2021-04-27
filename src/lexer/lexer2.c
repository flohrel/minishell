/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 05:14:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/28 01:23:08 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	job_token_handle(int tk_type, t_vars *vars, char **c)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	printf("%c\n", *(*c + 1));
	if ((tk_type == TK_GREAT) && (get_token_type(*(*c + 1)) == TK_GREAT))
	{
		new_token(vars, TK_DGREAT, 0);
		(*c)++;
	}
	else
		new_token(vars, tk_type, 0);
}

void	word_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (**buf);
}

void	space_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;
	int		size;

	lexer = &vars->lexer;
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	size = lexer->buffer + lexer->buf_len - (*buf);
	new_token(vars, TOKEN, size);
}

void	escape_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = *(++(*buf));
}

void	quote_handle(t_vars *vars, char *buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (*buf);
	if ((*buf == '\'') || (*buf == '\"'))
		lexer->state = ST_GENERAL;
}
