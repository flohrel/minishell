/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/06 19:21:05 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	quote_handle(t_vars *vars, char *buf)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	*(lexer->cur_char)++ = (*buf);
	if (((*buf == '\'') && (lexer->state == ST_QUOTE))
		|| ((*buf == '\"') && (lexer->state == ST_DQUOTE)))
		lexer->state = ST_GENERAL;
}

void	lexer_init(t_vars *vars, void (*token_handle[10])(t_vars *, int, char **))
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
	token_handle[5] = job_handle;
	token_handle[6] = job_handle;
	token_handle[7] = job_handle;
	token_handle[8] = redirection_handle;
	token_handle[9] = redirection_handle;
}

void	lexer(t_vars *vars, t_lexer *lexer)
{
	char	*buffer;
	int		tk_type;
	void	(*token_handle[10])(t_vars *, int, char **);

	lexer_init(vars, token_handle);
	buffer = lexer->buffer;
	while (*buffer)
	{
		tk_type = get_token_type(*buffer);
		printf("tk_type=%d\n", tk_type);
		if (lexer->state == ST_GENERAL)
			token_handle[tk_type](vars, tk_type, &buffer);
		else
			quote_handle(vars, buffer);
		buffer++;
	}
	if (lexer->cur_char)
		*(lexer->cur_char) = '\0';
	new_token(vars, TK_NL, 0);
}
