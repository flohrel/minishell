/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/27 04:30:01 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->tokens = NULL;
	lexer->buf_len = ft_strlen(lexer->buffer);
	lexer->cur_tok = NULL;
	lexer->cur_char = NULL;
	lexer->token_handle[0] = word_handle;
	lexer->token_handle[1] = word_handle;
	lexer->token_handle[2] = word_handle;
	lexer->token_handle[3] = space_handle;
	lexer->token_handle[4] = escape_handle;
}

int		lexer(t_vars *vars)
{
	char	*buffer;
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
				job_token_handle(tk_type, vars, &buffer);
			else
				token_handle[tk_type](vars, &buffer);
		}
		else
			quote_handle(vars);
		buffer++;
	}
	return (0);
}
