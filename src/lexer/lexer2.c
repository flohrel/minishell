/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 05:14:28 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/27 04:32:31 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	job_token_handle(int tk_type, t_vars *vars, char **c)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	if (lexer->cur_tok)
		*(lexer->cur_char) = '\0';
	if ((tk_type == TK_GREAT) && (*(*c + 1) == TK_GREAT))
	{
		new_token(vars, TK_DGREAT, 0);
		(*c)++;
	}
	else
		new_token(vars, tk_type, 0);
	lexer->cur_tok = NULL;
}

void	word_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = vars->lexer;
	token = lexer->cur_tok;
}

void	space_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = vars->lexer;
	token = lexer->cur_tok;
	cur_char = '\0';
}

void	escape_handle(t_vars *vars, char **buf)
{
	t_lexer	*lexer;

	lexer = vars->lexer;
	token = lexer->cur_tok;
	cur_char = '\0';
}

void	quote_handle(t_vars *vars)
{
	t_lexer	*lexer;

	lexer = vars->lexer;
	token = lexer->cur_tok;
	cur_char = '\0';
}
