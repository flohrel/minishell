/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/22 15:49:13 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->ntoken = 0;
	lexer->tokens = NULL;
}

void	job_token_handle(int tk_type, t_vars *vars, char *c)
{
	if ((tk_type == TK_GREAT) && (*(c + 1) == TK_GREAT))
		new_token(vars, TK_DGREAT, NULL);
	else
		new_token(vars, tk_type, NULL);
}

int		lexer(t_vars *vars)
{
	char	*c;
	int		tk_type;
	t_lexer	*lexer;

	lexer_init(vars);
	lexer = &vars->lexer;
	c = lexer->buffer;
	while (*c)
	{
		tk_type = get_token_type(*c);
		if (tk_type > 5 && (lexer->state == ST_GENERAL))
			job_token_handle(tk_type, vars, c);
		c++;
	}
	return (0);
}
