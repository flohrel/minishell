/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 05:32:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/07 15:34:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*list1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmp_node;
	t_ast	*list_node;
	int		node_type;

	if (!check_token(parser, TK_OPPAR | TK_COMPND))
		return (NULL);
	cmp_node = list(vars, parser);
	if ((cmp_node == NULL) || !check_token(parser, TK_CLPAR | TK_COMPND))
		return (NULL);
	set_flag(&cmp_node->type, NODE_SUB);
	node_type = get_node_type(parser);
	if (!node_type)
		return (NULL);
	list_node = list(vars, parser);
	if (list_node == NULL)
		return (NULL);
	node = tree_new_node(vars, node_type, NULL);
	tree_attach_branch(node, cmp_node, list_node);
	return (node);
}

t_ast	*list2(t_vars *vars, t_parser *parser)
{
	t_ast	*cmp_node;

	if (!check_token(parser, TK_OPPAR | TK_COMPND))
		return (NULL);
	cmp_node = list(vars, parser);
	if ((cmp_node == NULL) || !check_token(parser, TK_CLPAR | TK_COMPND))
		return (NULL);
	set_flag(&cmp_node->type, NODE_SUB);
	return (cmp_node);
}

t_ast	*list3(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmd_node;
	t_ast	*list_node;
	int		node_type;

	cmd_node = cmd(vars, parser);
	if (cmd_node == NULL)
		return (NULL);
	node_type = get_node_type(parser);
	if (!node_type)
		return (NULL);
	list_node = list(vars, parser);
	if (list_node == NULL)
		return (NULL);
	node = tree_new_node(vars, node_type, NULL);
	tree_attach_branch(node, cmd_node, list_node);
	return (node);
}
