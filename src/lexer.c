/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/16 18:10:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int		get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == ';')
		return (TK_SEMCOL);
	else if (c == '\'')
		return (TK_QUOTE);
	else if (c == '\"')
		return (TK_DQUOTE);
	else if (c == '\\')
		return (TK_ESCAPE);
	else if (c == '>')
		return (TK_RDOUT);
	else if (c == '<')
		return (TK_RDIN);
	else if (c == ' ')
		return (TK_SPACE);
	else
		return (TK_STR);
}

void	general_state_handle(t_vars *vars)
{
	(void)vars;
}

void	quote_state_handle(t_vars *vars)
{
	(void)vars;
}

void	dquote_state_handle(t_vars *vars)
{
	(void)vars;
}

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;

	lexer = &vars->lexer;
	lexer->buf_len = ft_strlen(lexer->buffer);
	lexer->ntoken = 0;
	lexer->token_list = ft_calloc(1, sizeof(*(lexer->token_list)));
	if (lexer->token_list == NULL)
		clean_exit(vars, 1);
	lexer->token_handle[0] = general_state_handle;
	lexer->token_handle[1] = quote_state_handle;
	lexer->token_handle[2] = dquote_state_handle;
}

int		lexer(t_vars *vars)
{
	int		i;
	int		type;
	t_lexer	*lexer;

	lexer_init(vars);
	lexer = &vars->lexer;
	i = -1;
	while (lexer->buffer[++i])
	{
		type = get_token_type(lexer->buffer[i]);
		lexer->token_handle[lexer->state](vars);
	}
	return (0);
}
