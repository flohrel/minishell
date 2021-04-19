/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:58:34 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/19 12:59:29 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	else if (c == '$')
		return (TK_VAR);
	else
		return (TK_STR);
}


