/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/25 05:15:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->ntoken = 0;
	lexer->tokens = NULL;
	lexer->token_handle[0] = word_handle;
	lexer->token_handle[1] = word_handle;
	lexer->token_handle[2] = word_handle;
	lexer->token_handle[3] = space_handle;
	lexer->token_handle[4] = escape_handle;
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
	char	*buffer;
	char	*cur_char;
	int		tk_type;
	t_lexer	*lexer;

	lexer_init(vars);
	lexer = &vars->lexer;
	buffer = lexer->buffer;
	while (*buffer)
	{
		tk_type = get_token_type(*buffer);
		if (lexer->state == ST_GENERAL)
		{
			if (tk_type > 6)
				job_token_handle(tk_type, vars, buffer);
			else
				token_handle[tk_type](vars, &buffer, cur_char);
		}
		else
			quoted_state_handle(vars, cur_char);
		buffer++;
	}
	return (0);
}
