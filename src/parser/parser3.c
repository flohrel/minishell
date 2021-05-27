/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 04:35:46 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 04:40:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_token(t_parser *parser, int type)
{
	t_token *token;

	token = (t_token *)parser->cur_tk->content;
	if (token->type != type)
		return (0);
	parser->cur_tk = parser->cur_tk->next;
	return (1);
}

t_ast	*cmdline(t_vars *vars, t_parser *parser)
{
	t_ast	*node;

	parser->prev_tk = parser->cur_tk;
	node = cmdline1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = parser->prev_tk;
	node = cmdline2(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = parser->prev_tk;
	node = job(vars, parser);
	if (node != NULL)
		return (node);
	return (NULL);
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
	node = tree_new_node(vars, NODE_SEQ, NULL);
	tree_attach_branch(node, job_node, NULL);
	return (node);
}

int		astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	parser->cur_tk = lexer->tk_list;
	parser->exec_tree = cmdline(vars, parser);
	if (parser->exec_tree == NULL)
		return (syntax_error(parser->cur_tk->content));
	return (0);
}
