/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/19 16:06:58 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	quote_state_handle(t_vars *vars, int tk_type)
{
	(void)vars;
	(void)tk_type;
}

void	dquote_state_handle(t_vars *vars, int tk_type)
{
	(void)vars;
	(void)tk_type;
}

void	general_state_handle(t_vars *vars, int tk_type)
{
	t_lexer	*lexer;
	(void)tk_type;

	lexer = &vars->lexer;
	if (lexer->tk_type == TK_SPACE)
	{

	}
}

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;
	t_token	*new_token;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->buf_len = ft_strlen(lexer->buffer);
	lexer->ntoken = 0;
	new_token = ft_calloc(1, sizeof(*new_token));
	if (new_token == NULL)
		clean_exit(vars, 1);
	lexer->tokens = ft_lstnew(new_token);
	lexer->token_handle[0] = general_state_handle;
	lexer->token_handle[1] = quote_state_handle;
	lexer->token_handle[2] = dquote_state_handle;
}

int		lexer(t_vars *vars)
{
	int		i;
	int		tk_type;
	t_lexer	*lexer;

	lexer_init(vars);
	lexer = &vars->lexer;
	i = -1;
	while (lexer->buffer[++i])
	{
		tk_type = get_token_type(lexer->buffer[i]);
		lexer->token_handle[lexer->state](vars, tk_type);
	}
	return (0);
}
