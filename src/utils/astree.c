/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:00:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/26 19:08:11 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_ast	*tree_new_node(t_vars *vars, int type, t_cmd *data)
{
	t_ast	*new_node;

	new_node = lst_alloc(1, sizeof(*new_node), &vars->ptr_list);
	if (new_node == NULL)
		clean_exit(vars, errno);
	new_node->type = type;
	new_node->data = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
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
