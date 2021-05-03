/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:03:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/03 16:58:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	get_token_char(int type)
{
	if (type == TK_PIPE)
		return ('|');
	else if (type == TK_SEMI)
		return (';');
	else if (type == TK_QUOTE)
		return ('\'');
	else if (type == TK_DQUOTE)
		return ('\"');
	else if (type == TK_ESC)
		return ('\\');
	else if (type == TK_GREAT)
		return ('>');
	else if (type == TK_LESS)
		return ('<');
	else if (type == TK_SPACE)
		return (' ');
	else
		return (0);
}

void	display_token_list(t_lexer *lexer)
{
	t_list	*lst;
	t_token	*token;

	lst = lexer->tokens;
	while (lst)
	{
		printf(GRN"["RESET);
		token = lst->content;
		if (token->type == TK_DGREAT)
			printf(BLU">>"RESET);
		else if (token->type == TOKEN)
			printf(MAG"%s"RESET, token->data);
		else
			printf(BLU"%c"RESET, get_token_char(token->type));
		printf(GRN"] "RESET);
		lst = lst->next;
	}
	printf("\n");
	fflush(stdout);
}
