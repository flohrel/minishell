/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 05:32:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/13 17:34:39 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
t_ast	*cmd(t_vars *vars, t_parser *parser)
{
	t_ast	*node;

	(void)vars;
	(void)node;
//	t_token *truc = (t_token *)parser->cur_tk->content;
//	printf("data:%s type:%d\n", truc->data, truc->type);
	parser->prev_tk = parser->cur_tk;
/*	node = cmd1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = parser->prev_tk;
	node = cmd2(vars, parser);
	if (node != NULL)
		return (node);
	node = cmd3(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = parser->prev_tk;
	node = cmd4(vars, parser);
	if (node != NULL)
		return (node);*/
	return (NULL);
}

t_ast	*job(t_vars *vars, t_parser *parser)
{
	t_ast	*node;

	parser->prev_tk = parser->cur_tk;
	node = job1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = parser->prev_tk;
	node = cmd(vars, parser);
	if (node != NULL)
		return (node);
	return (NULL);
}

t_ast	*job1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmd1_node;
	t_ast	*cmd2_node;

	cmd1_node = cmd(vars, parser);
	if (cmd1_node == NULL)
		return (cmd1_node);
	if (!check_token(parser, TK_PIPE))
	{
		tree_delete_node(cmd1_node);
		return (NULL);
	}
	cmd2_node = cmd(vars, parser);
	if (cmd2_node == NULL)
	{
		tree_delete_node(cmd1_node);
		return (cmd2_node);
	}
	node = tree_new_node(vars, NODE_PIPE, NULL);
	tree_attach_branch(node, cmd1_node, cmd2_node);
	return (node);
}
