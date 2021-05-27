/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 05:32:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 08:13:51 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
