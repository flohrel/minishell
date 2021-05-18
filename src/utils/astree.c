/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:00:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/18 02:40:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ast	*tree_new_node(t_vars *vars, int type, t_cmd *data)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(*new_node));
	if (new_node == NULL)
		clean_exit(vars, errno);
	new_node->type = type;
	new_node->data = NULL;
	if (data)
		new_node->data = data;
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
	if (node->type & NODE_CMD)
		free_cmd(&node->data);
	tree_delete_node(node->left);
	tree_delete_node(node->right);
}
