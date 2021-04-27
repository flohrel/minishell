/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:03:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/28 01:13:20 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	display_token_list(t_lexer *lexer)
{
	t_list	*lst;
	t_token	*token;

	lst = lexer->tokens;
	while (lst)
	{
		token = lst->content;
		printf("%d - %s\n", token->type, token->data);
		lst = lst->next;
	}
}
