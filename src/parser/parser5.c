/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:07:59 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/29 09:57:29 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		redirection(t_vars *vars, t_parser *parser, int type, t_param *data)
{
	t_token	*token;
	t_token	*redir;
	t_list	*lst;

	parser->cur_tk = parser->cur_tk->next;
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_WORD)
		return (-1);
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->next = NULL;
	redir = lst_alloc(1, sizeof(*redir), vars);
	redir->type = type;
	redir->data = token->data;
	lst->content = redir;
	ft_lstadd_back(&data->redir, lst);
	return (0);
}

void	argument(t_vars *vars, t_token *token, t_param *data)
{
	t_list	**dest_list;
	t_list	*lst;
	t_token	*param;
	char	*ptr;

	dest_list = &data->arg;
	if (!data->has_path)
	{
		if (((ptr = ft_strchr(token->data, '+')) ||
			(ptr = ft_strchr(token->data, '='))) && (ptr != token->data))
			dest_list = &data->assign;
		else
		{
			data->path = token->data;
			data->has_path = true;
			return ;
		}
	}
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->next = NULL;
	param = lst_alloc(1, sizeof(*param), vars);
	param->type = TK_WORD;
	param->data = token->data;
	lst->content = param;
	ft_lstadd_back(dest_list, lst);
}

t_param	*init_cmd_param(t_vars *vars)
{
	t_param	*data;

	data = lst_alloc(1, sizeof(*data), vars);
	data->path = NULL;
	data->redir = NULL;
	data->arg = NULL;
	data->assign = NULL;
	data->has_path = false;
	return (data);
}

t_ast	*cmd(t_vars *vars, t_parser *parser)
{
	t_param	*data;
	t_token	*token;

	token = (t_token *)parser->cur_tk->content;
	if (token->type < 0)
		return (NULL);
	data = init_cmd_param(vars);
	while ((token->type == TK_WORD) || (token->type > TK_SEMI))
	{
		if (token->type == TK_WORD)
			argument(vars, token, data);
		else if (redirection(vars, parser, token->type, data) == -1)
			return (NULL);
		parser->cur_tk = parser->cur_tk->next;
		token = (t_token *)parser->cur_tk->content;
	}
	return (tree_new_node(vars, NODE_CMD, data));
}
