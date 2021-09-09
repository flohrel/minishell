/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 05:32:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/09 15:57:40 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_node_type(t_parser *parser)
{
	if (check_token(parser, TK_DAMP))
		return (NODE_AND | NODE_LIST);
	if (check_token(parser, TK_DPIPE))
		return (NODE_OR | NODE_LIST);
	return (0);
}

t_ast	*list1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmp_node;
	t_ast	*list_node;
	int		node_type;

	if (!check_token(parser, TK_OPPAR))
		return (NULL);
	cmp_node = list(vars, parser);
	if ((cmp_node == NULL) || !check_token(parser, TK_CLPAR))
		return (NULL);
	set_flag(&cmp_node->type, NODE_SUB);
	node_type = get_node_type(parser);
	if (node_type)
	{
		list_node = list(vars, parser);
		if (list_node == NULL)
			return (NULL);
		node = tree_new_node(vars, node_type, NULL);
		tree_attach_branch(node, cmp_node, list_node);
	}
	else
		node = cmp_node;
	return (node);
}

t_ast	*list2(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*job_node;
	t_ast	*list_node;
	int		node_type;

	job_node = job(vars, parser);
	if (job_node == NULL)
		return (NULL);
	node_type = get_node_type(parser);
	if (node_type)
	{
		list_node = list(vars, parser);
		if (list_node == NULL)
			return (NULL);
		node = tree_new_node(vars, node_type, NULL);
		tree_attach_branch(node, job_node, list_node);
	}
	else
		node = job_node;
	return (node);
}

t_ast	*job(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_list	*save;

	save = parser->cur_tk;
	node = pipeline(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = cmd(vars, parser);
	return (node);
}

t_ast	*pipeline(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmd_node;
	t_ast	*job_node;

	cmd_node = cmd(vars, parser);
	if (cmd_node == NULL)
		return (NULL);
	if (!check_token(parser, TK_PIPE))
		return (NULL);
	job_node = job(vars, parser);
	if (job_node == NULL)
		return (NULL);
	node = tree_new_node(vars, NODE_PIPE, NULL);
	tree_attach_branch(node, cmd_node, job_node);
	return (node);
}
