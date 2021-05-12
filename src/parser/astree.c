/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:00:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/12 04:26:15 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*tree_new_node(t_vars *vars, int type, char *data)
{
	t_ast	*new_node;
	int		data_size;

	new_node = ft_calloc(1, sizeof(*new_node));
	if (new_node == NULL)
		clean_exit(vars, errno);
	new_node->type = type;
	new_node->data = NULL;
	if (data)
	{
		new_node->type |= NODE_DATA;
		data_size = ft_strlen(data);
		new_node->data = ft_calloc(data_size + 1, sizeof(*data));
		if (new_node->data == NULL)
			clean_exit(vars, errno);
		ft_strlcpy(new_node->data, data, data_size + 1);
	}
	return (new_node);
}

void	tree_attach_branch(t_ast *root, t_ast *left, t_ast *right)
{
	if (root != NULL)
	{
		root->left = left;
		root->right = right;
	}
}

void	tree_delete_node(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->data);
	tree_delete_node(node->left);
	tree_delete_node(node->right);
}

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
	t_list	*save;

	save = parser->cur_tk;
	node = cmdline1(parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = cmdline2(parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	node = cmdline3(parser);
	if (node != NULL)
		return (node);
	parser->cur_tk = save;
	return (NULL);
}

t_ast	*cmdline1(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*job_node;
	t_ast	*cmdline_node;

	job_node = job(vars, parser);
	if (job_node == NULL)
		return (job_node);
	if (!check_token(parser, TK_SEMI))
	{
		tree_delete_node(job_node);
		return (NULL);
	}
	cmdline_node = cmdline(vars, parser);
	if (cmdline_node == NULL)
	{
		tree_delete_node(job_node);
		return (cmdline_node);
	}
	node = tree_new_node(vars, NODE_SEQ, NULL);
	tree_attach_branch(node, job_node, cmdline_node);
	return (node);
}

t_ast	*cmdline2(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_ast	*job_node;

	job_node = job(vars, parser);
	if (node == NULL)
		return (node);
	node = tree_new_node(vars, NODE_SEQ, NULL);
	tree_attach_branch(node, job_node, cmdline_node);
	return (node);

}

t_ast	*cmdline3(t_vars *vars, t_parser *parser)
{
}

void	astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	(void)vars;
	(void)lexer;
	(void)parser;
	parser->cur_tk = lexer->tk_list;
	parser->exec_tree = cmdline(vars, parser);
	return (NULL);
}
