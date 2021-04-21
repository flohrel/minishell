/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/20 14:23:44 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	lexer_init(t_vars *vars)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = &vars->lexer;
	lexer->state = ST_GENERAL;
	lexer->buf_len = ft_strlen(lexer->buffer);
	lexer->ntoken = 0;
	token = new_token(TOKEN);
	if (token == NULL)
		clean_exit(vars, errno);
	lexer->tokens = ft_lstnew(new_token);
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
		printf("%d\n", tk_type);
	}
	return (0);
}
