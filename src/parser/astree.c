/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 01:00:42 by flohrel           #+#    #+#             */
<<<<<<< HEAD:src/utils/astree.c
/*   Updated: 2021/05/18 17:21:22 by flohrel          ###   ########.fr       */
=======
/*   Updated: 2021/05/12 04:36:24 by flohrel          ###   ########.fr       */
>>>>>>> parent of d390540... debugging tree parsing:src/parser/astree.c
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
	new_node->left = NULL;
	new_node->right = NULL;
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
<<<<<<< HEAD:src/utils/astree.c
	if (node->data)
		free_cmd_node(node->data);
=======
	if (node->type & NODE_DATA)
		free(node->data);
>>>>>>> parent of d390540... debugging tree parsing:src/parser/astree.c
	tree_delete_node(node->left);
	tree_delete_node(node->right);
	free(node);
}
