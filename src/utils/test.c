/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:03:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 03:18:00 by flohrel          ###   ########.fr       */
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

void	tree_display(t_ast *node, int level, int side)
{
	if (node == NULL)
		return ;
	printf("type=%d/level=%d/side=", node->type, level);
	if (!side)
		printf("racine\n");
	else if (side == -1)
		printf("left\n");
	else
		printf("right\n");
	tree_display(node->left, level + 1, -1);
	tree_display(node->right, level + 1, 1);
}
