/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/17 23:33:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_init(t_vars *vars, void (*token_handle[5])(t_vars *, char **))
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->buf_len = ft_strlen(lexer->buffer);
	new_token(vars, TK_WORD, lexer->buf_len);
	token_handle[0] = word_handle;
	token_handle[1] = word_handle;
	token_handle[2] = word_handle;
	token_handle[3] = space_handle;
	token_handle[4] = escape_handle;
}

void	lexer(t_vars *vars, t_lexer *lexer)
{
	char	*buffer;
	int		tk_type;
	void	(*token_handle[5])(t_vars *, char **);

	lexer_init(vars, token_handle);
	buffer = lexer->buffer;
	while (*buffer)
	{
		tk_type = get_token_type(*buffer);
		if (lexer->state == ST_GENERAL)
		{
			if (tk_type >= 5)
				job_token_handle(tk_type, vars, &buffer);
			else
				token_handle[tk_type](vars, &buffer);
		}
		else
			quote_handle(vars, buffer);
		buffer++;
	}
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	new_token(vars, TK_NL, 0);
}
