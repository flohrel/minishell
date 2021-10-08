/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 21:03:22 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/08 20:19:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_node_type(t_parser *parser)
{
	if (check_token(parser, (TK_DAMP | TK_LIST)))
		return (NODE_AND | NODE_LIST);
	if (check_token(parser, (TK_DPIPE | TK_LIST)))
		return (NODE_OR | NODE_LIST);
	if (check_token(parser, (TK_PIPE)))
		return (NODE_PIPE);
	return (0);
}

int	astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token	*cur_tk;
	t_token	*first_tk;

	clean_token_list(lexer, parser);
	parser->cur_tk = lexer->tk_list;
	vars->exec_tree = list(vars, parser);
	cur_tk = (t_token *)parser->cur_tk->content;
	first_tk = (t_token *)lexer->tk_list->content;
	if ((cur_tk->type != TK_NL)
		|| ((vars->exec_tree == NULL) && (first_tk->type != TK_NL)))
		return (syntax_error(cur_tk));
	return (0);
}

t_ast	*list(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_list	*save;

	save = parser->cur_tk;
	node = list1(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = list2(vars, parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = job(vars, parser);
	return (node);
}

t_ast	*list1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*cmp_node;
	t_ast	*list_node;
	int		node_type;

	cmp_node = subshell(vars, parser);
	if (cmp_node == NULL)
		return (NULL);
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
	t_ast	*node;
	t_ast	*job_node;
	t_ast	*list_node;
	int		node_type;

	job_node = job(vars, parser);
	if (job_node == NULL)
		return (NULL);
	node_type = get_node_type(parser);
	if (!node_type)
		return (NULL);
	list_node = list(vars, parser);
	if (list_node == NULL)
		return (NULL);
	node = tree_new_node(vars, node_type, NULL);
	tree_attach_branch(node, job_node, list_node);
	return (node);
}
