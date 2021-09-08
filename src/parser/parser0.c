/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/08 13:32:41 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_word(t_vars *vars, char **word)
{
	char	buffer[2][BUFFER_SIZE];
	int		len;

	param_expansion(vars, *word, buffer[0]);
	path_expansion(vars, buffer[0], buffer[1]);
	len = ft_strlen(buffer[1]);
	if (len == 0)
	{
		*word = NULL;
		return ;
	}
	*word = lst_alloc(len + 1, sizeof(*word), vars);
	ft_strlcpy(*word, buffer[1], len + 1);
}

void	parse_list(t_vars *vars, t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = (t_token *)lst->content;
		parse_word(vars, &token->data);
		lst = lst->next;
	}
}

void	parse_param(t_vars *vars, t_param *data)
{
	if (data->path)
		parse_word(vars, &data->path);
	parse_list(vars, data->redir);
	parse_list(vars, data->arg);
	parse_list(vars, data->assign);
}

void	parse_expansion(t_vars *vars, t_ast *node)
{
	if (!node)
		return ;
	if (check_flag(node->type, NODE_CMD))
		parse_param(vars, node->data);
	else
	{
		parse_expansion(vars, node->left);
		parse_expansion(vars, node->right);
	}
}
