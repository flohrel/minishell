/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/20 15:26:05 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_word(t_vars *vars, char **word)
{
	char	buffer[2][BUFFER_SIZE];
	int		len;

	param_expansion(vars, *word, buffer[0]);
	path_expansion(vars, buffer[0], buffer[1]);
	delete_quote(buffer[1], buffer[0]);
	len = ft_strlen(buffer[0]);
	*word = lst_alloc(len + 1, sizeof(**word), vars);
	ft_strlcpy(*word, buffer[0], len + 1);
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

void	parse_arg_list(t_vars *vars, t_list **args)
{
	char	buffer[2][BUFFER_SIZE];
	t_list	*lst;
	t_list	*new_lst;
	t_token	*token;

	lst = *args;
	*args = NULL;
	while (lst)
	{
		token = (t_token *)lst->content;
		param_expansion(vars, token->data, buffer[0]);
		path_expansion(vars, buffer[0], buffer[1]);
		new_lst = word_splitting(vars, buffer[1]);
		ft_lstadd_back(args, new_lst);
		lst = lst->next;
	}
	clean_arg_list(args);
	unquote_arg_list(*args);
}

void	parse_param(t_vars *vars, t_param *data)
{
	parse_arg_list(vars, &data->arg);
	if (data->arg)
	{
		data->path = ((t_token *)(data->arg->content))->data;
		data->arg = data->arg->next;
	}
	parse_list(vars, data->redir);
	parse_list(vars, data->assign);
	if (parse_redir(vars, data) == -1)
		data->to_exec = false;
	else
		data->to_exec = true;
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
