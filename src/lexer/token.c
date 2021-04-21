/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:58:34 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/20 14:24:43 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == ';')
		return (TK_SEMI);
	else if (c == '\'')
		return (TK_QUOTE);
	else if (c == '\"')
		return (TK_DQUOTE);
	else if (c == '\\')
		return (TK_ESC);
	else if (c == '>')
		return (TK_GREAT);
	else if (c == '<')
		return (TK_LESS);
	else if (c == ' ')
		return (TK_SPACE);
	else if (c == '$')
		return (TK_VAR);
	else
		return (TK_STR);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->data)
		free(token->data);
}

t_token	*new_token(int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (token);
	token->type = type;
	return (token);
}
