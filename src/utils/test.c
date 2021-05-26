/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:03:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/26 22:30:35 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	display_token_list(t_lexer *lexer)
{
	t_list	*lst;
	t_token	*token;

	lst = lexer->tk_list;
	while (lst)
	{
		printf(GRN"["RESET);
		token = lst->content;
		if (token->type == TK_DGREAT)
			printf(BLU">>"RESET);
		else if (token->type == TK_NL)
			printf(BLU"newline"RESET);
		else if (token->type == TK_WORD)
			printf(MAG"%s"RESET, token->data);
		else
			printf(BLU"%c"RESET, get_token_char(token->type));
		printf(GRN"] "RESET);
		lst = lst->next;
	}
	printf("\n");
	fflush(stdout);
}

void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("content : %p\n", lst->content);
		lst = lst->next;
	}
	printf("------------\n");
}
