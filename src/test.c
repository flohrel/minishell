/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 01:03:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/30 18:35:16 by flohrel          ###   ########.fr       */
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

void	print_content(void *content)
{
	printf("\"%s\" ", ((t_token *)content)->data);
}

void	print_tabs(int size)
{
	char	*vert = "\x1b(0\x78\x1b(B";

	while (size)
	{
		printf("%s", vert);
		printf("\t");
		size--;
	}
}

void	tree_display(t_ast *node, int level, int is_right)
{
	char	*root = "\x1b(0\x74\x1b(B";
	char	*horiz = "\x1b(0\x71\x1b(B";
	char	*branch = "\x1b(0\x6d\x1b(B";

	if (node == NULL)
		return ;
	print_tabs(level);
	if (!is_right || (node->type == NODE_CMD))
		printf("%s ", root);
	else
		printf("%s ", branch);
	if (node->type == NODE_SEQ)
		printf("SEQ");
	else if (node->type == NODE_PIPE)
		printf("PIPE");
	else
	{
		printf("CMD\n");
		print_tabs(level);
		printf("%s%s path: \"%s\"\n", root, horiz, node->data->path);
		print_tabs(level);
		printf("%s%s %d args: ", root, horiz, ft_lstsize(node->data->arg));
		ft_lstiter(node->data->arg, print_content);
		printf("\n");
		print_tabs(level);
		printf("%s%s %d redir: ", root, horiz, ft_lstsize(node->data->redir));
		ft_lstiter(node->data->redir, print_content);
		printf("\n");
		print_tabs(level);
		printf("%s%s %d assign: ", branch, horiz, ft_lstsize(node->data->assign));
		ft_lstiter(node->data->assign, print_content);
		printf("\n");
		return ;
	}
	printf("\n");
	tree_display(node->left, level + 1, 0);
	tree_display(node->right, level + 1, 1);
}
