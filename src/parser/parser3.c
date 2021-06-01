/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 04:35:46 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/01 15:44:00 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_token(t_parser *parser, int type)
{
	t_token	*token;

	token = (t_token *)parser->cur_tk->content;
	if (token->type != type)
		return (0);
	parser->cur_tk = parser->cur_tk->next;
	return (1);
}

t_ast	*cmdline(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_list	*save;

	save = parser->cur_tk;
	node = cmdline1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = cmdline2(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = job(vars, parser);
	return (node);
}

t_ast	*cmdline1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*job_node;
	t_ast	*cmdline_node;

	job_node = job(vars, parser);
	if (job_node == NULL)
		return (NULL);
	if (!check_token(parser, TK_SEMI))
		return (NULL);
	cmdline_node = cmdline(vars, parser);
	if (cmdline_node == NULL)
		return (NULL);
	node = tree_new_node(vars, NODE_SEQ, NULL);
	tree_attach_branch(node, job_node, cmdline_node);
	return (node);
}

t_ast	*cmdline2(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*job_node;

	job_node = job(vars, parser);
	if (job_node == NULL)
		return (NULL);
	if (!check_token(parser, TK_SEMI))
		return (NULL);
	node = tree_new_node(vars, NODE_SEQ, NULL);
	tree_attach_branch(node, job_node, NULL);
	return (node);
}
